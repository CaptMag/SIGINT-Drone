from scapy.all import *
import codecs
from subprocess import run, PIPE
import scapy.layers.dot11
def monitor_mode():

    NIC_Card_Name = input("Enter in your Wifi Network Interface Name: ") # Enter Physical NIC card

    network_interface = subprocess.check_output(["lspci" "|" "grep" "-i" "wireless"], shell=True).decode("utf-8")

    lines = network_interface.splitlines()
    if any("Wireless Network Adapter" in line for line in lines): # Check for Wireless Adapter in above command
        try:
            # Switches NIC into Monitor Mode
            command = (f"""
                sudo service network-manager stop && \
                sudo ifconfig {NIC_Card_Name} down && \
                sudo iwconfig {NIC_Card_Name} mode monitor && \
                sudo ifconfig {NIC_Card_Name} up && \
                sudo iwconfig {NIC_Card_Name} channel 11
                """)
            run(command, shell=True, check=True, stdout=PIPE, stderr=PIPE)
        except subprocess.CalledProcessError as e:
            print(f"Could not successfully convert {NIC_Card_Name} into monitor mode. Reason: {e}")
    else:
        print(f"Could not find physical Wireless Adapter")

    sniff(prn=probe_sniffer, iface=NIC_Card_Name) 

def probe_sniffer(p):

    if not (p.haslayer(scapy.layers.dot11.Dot11ProbeResp) or p.haslayer(scapy.layers.dot11.Dot11ProbeReq) or p.haslayer(scapy.layers.dot11.Dot11Beacon)): # Checks to see if beacon, and probes are available
        return
    try:
        # Setting up information
        rssi = p[scapy.layers.dot11.RadioTap].dBm_AntSignal
        dest_mac = p[scapy.layers.dot11].addr1
        src_mac = p[scapy.layers.dot11].addr2
        ap_mac = p[scapy.layers.dot11].addr2
        BSSID = p[scapy.layers.dot11].addr3
        info = f"rssi={rssi:2}dBm, dst={dest_mac}, src={src_mac}, ap={ap_mac}, BSSID={BSSID}"
    except KeyError as e:
        print(f"Error: {e}")

    # If probe resp is available, print it alongside its channel
    if p.haslayer(scapy.layers.dot11.Dot11ProbeResp):
        ssid = codecs.decode(p[scapy.layers.dot11.Dot11Elt].info, 'utf-8')
        elt = p[scapy.layers.dot11.Dot11Elt]
        # While loop to check for channel
        while isinstance(elt, scapy.layers.dot11.Dot11Elt):
            if elt.ID == 3:
                channel = elt.info[0]
                break
            elt = elt.payload
        print(f"[Probe Response] {info} | chan={channel} | ssid=\"{ssid}\"")

    # If probe req is available, print its info
    elif p.haslayer(scapy.layers.dot11.Dot11ProbeReq):
        print(f"[Probe Request] {info}")

    # if beacon is available, print its status, ssid(name) and beacon information
    elif p.haslayer(scapy.layers.dot11.Dot11Beacon):
        stats = p[scapy.layers.dot11.Dot11Beacon].network_stats()
        ssid = str(stats['ssid'])
        interval = p[scapy.layers.dot11.Dot11Beacon].beacon_interval()
        print(f"[BEACON] {info} | [CHAN] {channel} | [INTERVAL] = {interval} | [SSID] = {ssid}")

if __name__ == "__main__":
    monitor_mode()

from scapy.all import *
from subprocess import run, PIPE
def monitor_mode():

    NIC_Card_Name = input("Enter in your Wifi Network Interface Name: ")

    network_interface = subprocess.check_output(["lspci" "|" "grep" "-i" "wireless"]).decode("utf-8")

    lines = network_interface.splitlines()
    if "Wireless Network Adapter" in lines:
        try:
            run("sudo service network-manager stop",
                f"sudo ifconfig {NIC_Card_Name} down",
                f"sudo iwconfig {NIC_Card_Name} mode monitor",
                f"sudo ifconfig {NIC_Card_Name} up",
                f"sudo iwconfig {NIC_Card_Name} channel 11", shell=True, check=True, stdout=PIPE, stderr=PIPE)
        except subprocess.CalledProccessError as e:
            print(f"Could not successfully convert {NIC_Card_Name} into monitor mode. Reason: {e}")
    else:
        print(f"Could not find physical Wireless Adapter")


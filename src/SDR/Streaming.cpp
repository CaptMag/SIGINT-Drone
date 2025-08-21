#include "UTILS.h"
#include "enumeration.h"
#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

/*--------------Starting Streaming---------------*/

SoapySDR::Stream* StreamSetup(SoapySDR::Device* device,
	int direction,
	const std::string& format,
	const std::vector<size_t>& channels,
	const SoapySDR::Kwargs& args,
	const int flags,
	const long long timeNs,
	const size_t numElems)

{

	puts("===============[Starting Stream!]===============");

	SoapySDR::Stream* stream = device->setupStream(direction, format, channels, args);
	try {
		device->activateStream(stream);
		device->setFrequency(SOAPY_SDR_RX, 1, 100e6);
		device->setGain(SOAPY_SDR_RX, 0, 30);
		device->setSampleRate(SOAPY_SDR_RX, 0, 2e6);
	}
	catch (exception& e)
	{
		warn("Error! Operation Terminated: %s", e.what());
		return nullptr;
	}
	return stream;
}


/*-----------------Reading Stream and Creating GUI-----------------------*/

int GUI(SoapySDR::Device* device, SoapySDR::Stream* stream)
{

	if (!glfwInit())
	{
		warn("Warning! Could not load GUI plotter!");
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(800, 600, "SDR Sample Rates", NULL, NULL);

	if (!window)
	{
		warn("Could not build SDR Sample Rate Window, terminating operation!");
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Setting up ImGui

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	// backends

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	std::vector<std::complex<float>> buff(1024);
	void* buffs[] = { buff.data() };

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("SDR Sample Rates");
		if (ImPlot::BeginPlot("Sample Rates"))
		{

			int flags = 0;
			long long timeNs = 0;
			int read_stream = device->readStream(stream, buffs, 1024, flags, timeNs, 100000);

			if (read_stream > 0)
			{
				static float t[1024], i_data[1024], q_data[1024];
				for (size_t i = 0; i < read_stream; i++) {
					t[i] = static_cast<float>(i);
					i_data[i] = buff[i].real();
					q_data[i] = buff[i].imag();
				}
				ImPlot::PlotLine("I", t, i_data, read_stream);
				ImPlot::PlotLine("Q", t, q_data, read_stream);
			}
			else {
				ImGui::Text("Wating for samples....");
			}
			ImPlot::EndPlot();
		}
		ImGui::End();

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
	device->deactivateStream(stream);
	device->closeStream(stream);

	return EXIT_SUCCESS;
}

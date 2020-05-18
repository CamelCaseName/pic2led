#include "pic2led.h"

using namespace std;

int main()
{
	std::string strtmp;
	cout << "Please specify the full location of the image" << endl;
	std::getline(std::cin, strtmp); //get path
	const char* path = strtmp.c_str(); //parse path
	try {
		BMP in(path);//get file into bmp struct
		in.bmp_info_header.height = abs(in.bmp_info_header.height);
		in.bmp_info_header.width = abs(in.bmp_info_header.width);
		if ((in.bmp_info_header.width <= 64 && in.bmp_info_header.height <= 32) || (in.bmp_info_header.width <= 32 && in.bmp_info_header.height <= 64)) //check for size
		{
			cout << "Size is correct (max 32x64 or 64x32)" << endl; // output size

			uint8_t lvl;
			cout << "Please give a number between 0 and 255 for the colordepth reduction level" << endl; //get level for color bit reduction
			std::getline(std::cin,strtmp);
			lvl = std::stoul(strtmp,nullptr,10);

			cout << "specify the path for the output file" << endl;
			strtmp = "";
		
			std::getline( std::cin,strtmp); //get location
			const char* txtpath = strtmp.c_str(); //convert
			std::ofstream of(txtpath); //create output file
		
			if (of) {
				uint8_t channels = in.bmp_info_header.bit_count / 8;
				of << "static LEDx8 f[256]" << endl;

				cout << in.bmp_info_header.width << "wxh" << in.bmp_info_header.height << endl;

				uint16_t tmp1 = 0;
				uint8_t tmp2 = 0;
				if (in.bmp_info_header.height <= 32) { // landscape
					for (uint8_t y = 0; y < in.bmp_info_header.height; y++) {
						for (uint8_t x = 0; x < in.bmp_info_header.width; x++) {
							if (tmp2 < 8) {
								++tmp2;
							}
							else {
								tmp2 = 1;
							}
							if (in.data[channels * ((in.bmp_info_header.height - y - 1) * in.bmp_info_header.width + x) + 0] >= lvl) {
								in.data[channels * ((in.bmp_info_header.height - y - 1) * in.bmp_info_header.width + x) + 0] = 255; // set BLUE to maximum
								of << "f[" << tmp1 / 8 << "].bc" << tmp2 + 0 << "=1;"; //write blue information for pixel
							}
							else {
								in.data[channels * ((in.bmp_info_header.height - y - 1) * in.bmp_info_header.width + x) + 0] = 0; // set BLUE to 0
								of << "f[" << tmp1 / 8 << "].bc" << tmp2 + 0 << "=0;"; //write blue information for pixel
							}

							if (in.data[channels * ((in.bmp_info_header.height - y - 1) * in.bmp_info_header.width + x) + 1] >= lvl) { //set GREEN to maximum
								in.data[channels * ((in.bmp_info_header.height - y - 1) * in.bmp_info_header.width + x) + 1] = 255;
								of << "f[" << tmp1 / 8 << "].gc" << tmp2 + 0 << "=1;"; //write blue information for pixel
							}
							else {
								in.data[channels * ((in.bmp_info_header.height - y - 1) * in.bmp_info_header.width + x) + 1] = 0; // set GREEN to 0
								of << "f[" << tmp1 / 8 << "].gc" << tmp2 + 0 << "=0;"; //write blue information for pixel
							}

							if (in.data[channels * ((in.bmp_info_header.height - y - 1) * in.bmp_info_header.width + x) + 2] >= lvl) { //set RED to maximum
								in.data[channels * ((in.bmp_info_header.height - y - 1) * in.bmp_info_header.width + x) + 2] = 255;
								of << "f[" << tmp1 / 8 << "].rc" << tmp2 + 0 << "=1;"; //write blue information for pixel
							}
							else {
								in.data[channels * ((in.bmp_info_header.height - y - 1) * in.bmp_info_header.width + x) + 2] = 0; // set RED to 0
								of << "f[" << tmp1 / 8 << "].rc" << tmp2 + 0 << "=0;"; //write blue information for pixel
							}
							//vars for the format thingy
							tmp1++;
						}
					}
				}
				else { // portrait
					for (uint8_t x = 0; x < in.bmp_info_header.width; x++) {
						for (uint8_t y = 0; y < in.bmp_info_header.height; y++) {
							if (tmp2 < 8) {
								++tmp2;
							}
							else {
								tmp2 = 1;
							}
							if (in.data[channels * (y * in.bmp_info_header.width + x) + 0] >= lvl) {
								in.data[channels * (y * in.bmp_info_header.width + x) + 0] = 255; // set BLUE to maximum
								of << "f[" << tmp1 / 8 << "].bc" << tmp2 + 0 << "=1;"; //write blue information for pixel
							}
							else {
								in.data[channels * (y * in.bmp_info_header.width + x) + 0] = 0; // set BLUE to 0
								of << "f[" << tmp1 / 8 << "].bc" << tmp2 + 0 << "=0;"; //write blue information for pixel
							}

							if (in.data[channels * (y * in.bmp_info_header.width + x) + 1] >= lvl) { //set GREEN to maximum
								in.data[channels * (y * in.bmp_info_header.width + x) + 1] = 255;
								of << "f[" << tmp1 / 8 << "].gc" << tmp2 + 0 << "=1;"; //write blue information for pixel
							}
							else {
								in.data[channels * (y * in.bmp_info_header.width + x) + 1] = 0; // set GREEN to 0
								of << "f[" << tmp1 / 8 << "].gc" << tmp2 + 0 << "=0;"; //write blue information for pixel
							}

							if (in.data[channels * (y * in.bmp_info_header.width + x) + 2] >= lvl) { //set RED to maximum
								in.data[channels * (y * in.bmp_info_header.width + x) + 2] = 255;
								of << "f[" << tmp1 / 8 << "].rc" << tmp2 + 0 << "=1;"; //write blue information for pixel
							}
							else {
								in.data[channels * (y * in.bmp_info_header.width + x) + 2] = 0; // set RED to 0
								of << "f[" << tmp1 / 8 << "].rc" << tmp2 + 0 << "=0;"; //write blue information for pixel
							}
							//vars for the format thingy
							tmp1++;
						}
					}
				}
				if (in.bmp_info_header.height > 32) {
					BMP ifcopy(32, 64, false);
					ifcopy.data = in.data;
					string t = path;
					t.replace(t.end() - 4, t.end(), "");
					t += "copy.bmp";
					const char* ifcopypath = t.c_str();
					ifcopy.write(ifcopypath);		//output manipualted image
				}
				else{
					BMP ifcopy(64, 32, false);
					ifcopy.data = in.data;
					string t = path;
					t.replace(t.end()-4,t.end(), "");
					t += "copy.bmp";
					const char* ifcopypath = t.c_str();
					ifcopy.write(ifcopypath);		//output manipualted image
				}
				
				
				of.close();
				cout << "done" << endl;
			}		
		}
		else {
			cout << "Size is wrong: " << in.bmp_info_header.width << "x" << in.bmp_info_header.height << ", should be a maximum of 32x64 or 64x32."<< endl;

		}
	}
	catch (runtime_error e) {
		cout << "File cannot be loaded, check path" << endl;
	}
	return 0;
}
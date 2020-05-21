#include "pic2led.h"

using namespace std;

int main()
{
	//std::vector<uint8_t>tempdata;
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
				of << "static LEDx8 f[256] //just copy this upper part into the clss and the second line into the setup" << endl;

				cout << in.bmp_info_header.width << "wxh" << in.bmp_info_header.height << endl;

				//tempdata.resize(64*2*channels);
			

				uint16_t tmp1 = 0;
				uint8_t tmp2 = 0;
				uint8_t tmpr = 0;
				uint8_t tmpg = 0;
				uint8_t tmpb = 0;
				
				if (in.bmp_info_header.height <= 32) { // landscape
					/*
					//not needed anymore
					//copy rows 31 and 15
					for (uint8_t x = 0; x < 64; x++){
						tempdata[channels * x + 0] = in.data[channels * (31 * in.bmp_info_header.width + x) + 0]; //copy blue data
						tempdata[channels * x + 1] = in.data[channels * (31 * in.bmp_info_header.width + x) + 1]; //copy green data
						tempdata[channels * x + 2] = in.data[channels * (31 * in.bmp_info_header.width + x) + 2]; //copy red data
						tempdata[channels * (1 * 64 + x) + 0] = in.data[channels * (15 * in.bmp_info_header.width + x) + 0]; //copy blue data
						tempdata[channels * (1 * 64 + x) + 1] = in.data[channels * (15 * in.bmp_info_header.width + x) + 1]; //copy green data
						tempdata[channels * (1 * 64 + x) + 2] = in.data[channels * (15 * in.bmp_info_header.width + x) + 2]; //copy red data
					}

					//move whole picture up by one
					for (uint8_t y = in.bmp_info_header.height - 1; y > 1; y--) {
						for (uint8_t x = 0; x < in.bmp_info_header.width; x++) {
							//shift whole image left/down
							in.data[channels * (y * in.bmp_info_header.width + x) + 0] = in.data[channels * ((y - 1) * in.bmp_info_header.width + x) + 0]; //blue
							in.data[channels * (y * in.bmp_info_header.width + x) + 1] = in.data[channels * ((y - 1) * in.bmp_info_header.width + x) + 1]; //green
							in.data[channels * (y * in.bmp_info_header.width + x) + 2] = in.data[channels * ((y - 1) * in.bmp_info_header.width + x) + 2]; //red
						}
					}

					//reinsert rows 31 and 15 at 16 and 0
					for (uint8_t x = 0; x < 64; x++) {
						in.data[channels * (16 * in.bmp_info_header.width + x) + 0] = tempdata[channels * x + 0]; //copy blue data
						in.data[channels * (16 * in.bmp_info_header.width + x) + 1] = tempdata[channels * x + 1]; //copy green data
						in.data[channels * (16 * in.bmp_info_header.width + x) + 2] = tempdata[channels * x + 2]; //copy red data
						in.data[channels * (0 * in.bmp_info_header.width + x) + 0] = tempdata[channels * (1 * 64 + x) + 0]; //copy blue data
						in.data[channels * (0 * in.bmp_info_header.width + x) + 1] = tempdata[channels * (1 * 64 + x) + 1]; //copy green data
						in.data[channels * (0 * in.bmp_info_header.width + x) + 2] = tempdata[channels * (1 * 64 + x) + 2]; //copy red data
					}*/
					//convert picture
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
					/*
					//copy rows 31 and 15
					for (uint8_t x = 0; x < 64; x++) {
						tempdata[channels * x + 0] = in.data[channels * (x * in.bmp_info_header.width + 0) + 0]; //copy blue data
						tempdata[channels * x + 1] = in.data[channels * (x * in.bmp_info_header.width + 0) + 1]; //copy green data
						tempdata[channels * x + 2] = in.data[channels * (x * in.bmp_info_header.width + 0) + 2]; //copy red data
						tempdata[channels * (1 * 64 + x) + 0] = in.data[channels * (x * in.bmp_info_header.width + 16) + 0]; //copy blue data
						tempdata[channels * (1 * 64 + x) + 1] = in.data[channels * (x * in.bmp_info_header.width + 16) + 1]; //copy green data
						tempdata[channels * (1 * 64 + x) + 2] = in.data[channels * (x * in.bmp_info_header.width + 16) + 2]; //copy red data
					}

					//move whole picture up by one
					for (uint8_t y = 0; y < in.bmp_info_header.height; y++) {
						for (uint8_t x = 0; x < in.bmp_info_header.width - 1; x++) {
							//shift whole image left/down
							in.data[channels * (y * in.bmp_info_header.width + x) + 0] = in.data[channels * (y * in.bmp_info_header.width + x + 1) + 0]; //blue
							in.data[channels * (y * in.bmp_info_header.width + x) + 1] = in.data[channels * (y * in.bmp_info_header.width + x + 1) + 1]; //green
							in.data[channels * (y * in.bmp_info_header.width + x) + 2] = in.data[channels * (y * in.bmp_info_header.width + x + 1) + 2]; //red
						}
					}

					//reinsert rows 31 and 15 at 16 and 0
					for (uint8_t x = 0; x < 64; x++) {
						in.data[channels * (x * in.bmp_info_header.width + 15) + 0] = tempdata[channels * x + 0]; //copy blue data
						in.data[channels * (x * in.bmp_info_header.width + 15) + 1] = tempdata[channels * x + 1]; //copy green data
						in.data[channels * (x * in.bmp_info_header.width + 15) + 2] = tempdata[channels * x + 2]; //copy red data
						in.data[channels * (x * in.bmp_info_header.width + 31) + 0] = tempdata[channels * (1 * 64 + x) + 0]; //copy blue data
						in.data[channels * (x * in.bmp_info_header.width + 31) + 1] = tempdata[channels * (1 * 64 + x) + 1]; //copy green data
						in.data[channels * (x * in.bmp_info_header.width + 31) + 2] = tempdata[channels * (1 * 64 + x) + 2]; //copy red data
					}
					*/
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
					t += "preview.bmp";
					const char* ifcopypath = t.c_str();
					ifcopy.write(ifcopypath);		//output manipualted image
				}
				else{
					BMP ifcopy(64, 32, false);
					ifcopy.data = in.data;
					string t = path;
					t.replace(t.end()-4,t.end(), "");
					t += "preview.bmp";
					const char* ifcopypath = t.c_str();
					ifcopy.write(ifcopypath);		//output manipualted image
				}
				
				of << endl;
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
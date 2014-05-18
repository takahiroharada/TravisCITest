#include <gtest/gtest.h>

#if defined(__APPLE__)
	#include <OpenCL/cl.h>
	#include <OpenCL/cl_ext.h>
	#include <OpenCL/cl_platform.h>
#else
	#include <CL/cl.h>
	#include <CL/cl_ext.h>
	#include <CL/cl_platform.h>
#endif


TEST(UnitTest, Test1)
{

}

TEST(UnitTest, Test2)
{

}

TEST(UnitTest, OCLQuery)
{
	for(int i=0; i<2; i++)
	{
		cl_device_type deviceType = (i==0)?CL_DEVICE_TYPE_CPU:CL_DEVICE_TYPE_GPU;
		cl_int status;

		cl_platform_id platform;
		{
			cl_uint nPlatforms = 0;
			status = clGetPlatformIDs(0, NULL, &nPlatforms);
	//		ADLASSERT( status == CL_SUCCESS );

			cl_platform_id pIdx[5];
			status = clGetPlatformIDs(nPlatforms, pIdx, NULL);
	//		ADLASSERT( status == CL_SUCCESS );

			for(cl_uint ie=0; ie<nPlatforms; ie++)
			{
				char buff[512];
				status = clGetPlatformInfo( pIdx[ie], CL_PLATFORM_VENDOR, 512, buff, 0 );
	//			ADLASSERT( status == CL_SUCCESS );
				printf("%s: %s\n", (i==0)?"CPU":"GPU", buff);

				cl_uint numDevice;
				status = clGetDeviceIDs( platform, deviceType, 0, NULL, &numDevice );

				printf("CL: %d %s Devices\n", (int)numDevice, (deviceType==CL_DEVICE_TYPE_GPU)? "GPU":"CPU");

				cl_device_id deviceIds[ 8 ];
				status = clGetDeviceIDs( platform, deviceType, numDevice, deviceIds, NULL );
//				ADLASSERT( status == CL_SUCCESS );

				status = clGetDeviceInfo( deviceIds[0], CL_DEVICE_NAME, sizeof(buff), &buff, NULL );
//				ADLASSERT( status == CL_SUCCESS );

				printf("[%s]\n", buff);				
			}
		}
	}
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

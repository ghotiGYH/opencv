//图像的Canny边缘检测  
//By MoreWindows (http://blog.csdn.net/MoreWindows)  
#include <opencv2/opencv.hpp>  
using namespace std;
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")  

IplImage *g_pSrcImage, *g_pCannyImg;
IplImage *g_pResizedSrcImage, *g_pResizedCannyImage;
const char *pstrWindowsCannyTitle = "边缘检测图";
const double rsScale = 0.5;

//cvCreateTrackbar的回调函数  
void on_trackbar(int threshold)
{
	//canny边缘检测  
	cvCanny(g_pSrcImage, g_pCannyImg, threshold, threshold * 3, 3);
	cvResize(g_pCannyImg, g_pResizedCannyImage, CV_INTER_AREA);
	cvShowImage(pstrWindowsCannyTitle, g_pResizedCannyImage);
}

int main()
{
	const char *pstrImageName = "picture.png";
	const char *pstrWindowsSrcTitle = "原图";
	const char *pstrWindowsToolBar = "Threshold";


	//从文件中载入图像的灰度图CV_LOAD_IMAGE_GRAYSCALE - 灰度图  
	g_pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_GRAYSCALE);
	g_pCannyImg = cvCreateImage(cvGetSize(g_pSrcImage), IPL_DEPTH_8U, 1);

	CvSize reSize;
	reSize.height = g_pSrcImage->height*rsScale;
	reSize.width = g_pSrcImage->width*rsScale;

	g_pResizedSrcImage = cvCreateImage(reSize, g_pSrcImage->depth, g_pSrcImage->nChannels);
	g_pResizedCannyImage = cvCreateImage(reSize, g_pCannyImg->depth, g_pCannyImg->nChannels);

	//创建窗口  
	cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowsCannyTitle, CV_WINDOW_AUTOSIZE);

	//创建滑动条  
	int nThresholdEdge = 1;
	cvCreateTrackbar(pstrWindowsToolBar, pstrWindowsCannyTitle, &nThresholdEdge, 100, on_trackbar);



	//在指定窗口中显示图像  
	cvResize(g_pSrcImage, g_pResizedSrcImage, CV_INTER_AREA);
	cvShowImage(pstrWindowsSrcTitle, g_pResizedSrcImage);
	on_trackbar(1);

	//等待按键事件  
	cvWaitKey();

	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(pstrWindowsCannyTitle);
	cvReleaseImage(&g_pSrcImage);
	cvReleaseImage(&g_pCannyImg);
	cvReleaseImage(&g_pResizedSrcImage);
	cvReleaseImage(&g_pResizedCannyImage);
	return 0;
}
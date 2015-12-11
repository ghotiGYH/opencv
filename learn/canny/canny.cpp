//ͼ���Canny��Ե���  
//By MoreWindows (http://blog.csdn.net/MoreWindows)  
#include <opencv2/opencv.hpp>  
using namespace std;
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")  

IplImage *g_pSrcImage, *g_pCannyImg;
IplImage *g_pResizedSrcImage, *g_pResizedCannyImage;
const char *pstrWindowsCannyTitle = "��Ե���ͼ";
const double rsScale = 0.5;

//cvCreateTrackbar�Ļص�����  
void on_trackbar(int threshold)
{
	//canny��Ե���  
	cvCanny(g_pSrcImage, g_pCannyImg, threshold, threshold * 3, 3);
	cvResize(g_pCannyImg, g_pResizedCannyImage, CV_INTER_AREA);
	cvShowImage(pstrWindowsCannyTitle, g_pResizedCannyImage);
}

int main()
{
	const char *pstrImageName = "picture.png";
	const char *pstrWindowsSrcTitle = "ԭͼ";
	const char *pstrWindowsToolBar = "Threshold";


	//���ļ�������ͼ��ĻҶ�ͼCV_LOAD_IMAGE_GRAYSCALE - �Ҷ�ͼ  
	g_pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_GRAYSCALE);
	g_pCannyImg = cvCreateImage(cvGetSize(g_pSrcImage), IPL_DEPTH_8U, 1);

	CvSize reSize;
	reSize.height = g_pSrcImage->height*rsScale;
	reSize.width = g_pSrcImage->width*rsScale;

	g_pResizedSrcImage = cvCreateImage(reSize, g_pSrcImage->depth, g_pSrcImage->nChannels);
	g_pResizedCannyImage = cvCreateImage(reSize, g_pCannyImg->depth, g_pCannyImg->nChannels);

	//��������  
	cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowsCannyTitle, CV_WINDOW_AUTOSIZE);

	//����������  
	int nThresholdEdge = 1;
	cvCreateTrackbar(pstrWindowsToolBar, pstrWindowsCannyTitle, &nThresholdEdge, 100, on_trackbar);



	//��ָ����������ʾͼ��  
	cvResize(g_pSrcImage, g_pResizedSrcImage, CV_INTER_AREA);
	cvShowImage(pstrWindowsSrcTitle, g_pResizedSrcImage);
	on_trackbar(1);

	//�ȴ������¼�  
	cvWaitKey();

	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(pstrWindowsCannyTitle);
	cvReleaseImage(&g_pSrcImage);
	cvReleaseImage(&g_pCannyImg);
	cvReleaseImage(&g_pResizedSrcImage);
	cvReleaseImage(&g_pResizedCannyImage);
	return 0;
}
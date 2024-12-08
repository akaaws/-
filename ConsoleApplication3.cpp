#include <opencv.hpp>
#include<iostream>
#include"types.h"
using namespace cv;
//int main()
//{
//	Mat ab;
//	;
//	
//	
//	ab = imread("C:/Users/jkl/Documents/Tencent Files/2662391693/nt_qq/nt_data/Pic/2024-11/Thumb/cfb7948e0939c53001cb4bd16635f6c3_720.jpg");
//	//图片的截取（rect，circle，explics）
//	Rect box(100,100, 1100, 800);//（坐标竖，坐标横，宽，长）
//	Mat ak = ab(box);
//	imshow("ak", ak);
//	imshow("ab", ab);
//
//	//色彩通道的分离，以灰度图的形式显示，越深其对应的通道值越高
//	//创立一个新的图篇
//
//	Mat ak = Mat::ones(Size(500, 500), CV_8UC3);
//	ak = Scalar(0, 255, 0);
//	//cvtColor(ab, aga, COLOR_BGR2HSV);
//	namedWindow("ak", 0);
//	std::vector<Mat> somg;
//	split(ak, somg);
//	imshow("as", somg[1]);
//	imshow("as2", somg[2]);
//	imshow("as3", somg[0]);
//	//imwrite("C:/Users/jkl/Downloads/try4.jpg",aga);
//	waitKey(10000);
//
//	return 0;
//}


//int main()//摄像头的调用
//{
//	VideoCapture cap(0);
//	while(true)
//	{
//		Mat fram;
//		cap >> fram;
//		Mat gray;
//		cvtColor(fram, gray, COLOR_BGR2GRAY);//转灰度图
//		Mat binary;
//		threshold(gray, binary, 100, 255, THRESH_BINARY);
//		imshow("try", binary);
//		char c = (char)waitKey(9);
//		if (c == 27)
//			break;
//		//imwrite("C:/Users/jkl/Downloads/try12.jpg", fram);
//	}
//	return 0;
//}
int main()
{
	VideoCapture cap("C:/Users/jkl/Downloads/test1.avi");
	double chang = cap.get(CAP_PROP_FRAME_HEIGHT);
	double kuan = cap.get(CAP_PROP_FRAME_WIDTH);
	double transmit = (chang * kuan) / 25.4;
	while (true)
	{
		Mat yuantu;
		Mat test = yuantu;
		Mat gray = yuantu;
		cap >> yuantu;
		if (yuantu.empty()) break;
		Mat test2 = yuantu.clone();
		//尝试通过特征提取直接识别装甲板，但效果不好且运行缓慢-_-
		// //Mat test = yuantu.clone();
		//Mat binary = test;
		//cvtColor(yuantu, test, COLOR_BGR2GRAY);
		//threshold(test, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
		//Mat sample = imread("C:/Users/jkl/Pictures/Screenshots/aka.png");
		//Mat sample2 = sample;
		////GaussianBlur(sample, sample2,Size(3,3), 1, 1);
		//Ptr<SIFT> sift = SIFT::create();
		//std::vector<KeyPoint> keypoint1s, keypoint2s;
		//Mat d1, d2;
		//sift->detectAndCompute(sample, noArray(), keypoint1s, d1);
		//sift->detectAndCompute(test, noArray(), keypoint2s, d2);
		//BFMatcher matcher(NORM_L2);
		//std::vector<DMatch> matches;
		//matcher.match(d1, d2, matches);
		//double minDist = 30;
		//double maxDist = 60;
		//std::vector<DMatch> goodmatches;
		//for (int i = 0; i < d1.rows; i++)
		//{
		//	double dist = matches[i].distance;
		//	if (dist<maxDist && dist>minDist)
		//		goodmatches.push_back(matches[1]);
		//}
		//Mat test2 = yuantu.clone();
		//drawMatches(sample, keypoint1s, yuantu, keypoint2s, goodmatches, test2);
		//Mat gray = yuantu;
	GaussianBlur(yuantu, test, Size(3, 3), 2, 2);
	cvtColor(test, gray, COLOR_BGR2GRAY);//转灰度图
	Mat binary;
	threshold(gray, binary, 200, 255, THRESH_BINARY);
	Mat guss = binary;
	std::vector<std::vector<Point>> contours;
	findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	/*Mat drawcountours = yuantu.clone();
	drawContours(drawcountours, contours, -1, Scalar(0, 0, 255), 2);*/
	//调试用
	std::vector<RotatedRect> roted_rects;
	std::vector<Lightbar> lightbars;
	for (const auto& contour : contours)
	{
		auto roted_rect = minAreaRect(contour);
		roted_rects.emplace_back(roted_rect);
		auto lightbar=Lightbar(roted_rect);
		if (isratioreal(lightbar, 12, 5))
			lightbars.emplace_back(lightbar);
	}
	//尝试通过灯条来识别装甲版，但判断条件单一，识别效果不好
	std::vector<Armor> armors;
	for (auto left = lightbars.begin(); left != lightbars.end(); left++)
	{
		for (auto right = left + 1; right != lightbars.end(); right++)
		{

			auto armor = Armor(*left, *right);
			if (armor.check_Armor())
				armors.emplace_back(armor);
		}
	}
	//展示框选效果
	
	for (const auto& armor : armors)
	{
		rectangle(test2, armor.left.top, armor.right.bottom, Scalar(255, 0, 0), 2);
	}
	//Mat drawract = yuantu.clone();
	//for (const auto& roted_rect : roted_rects)
	//{
	//	//std::cout << roted_rect.size.height/roted_rect.size.width<<std::endl;//求得长宽比
	//	Lightbar lightnar=Lightbar(roted_rect);
	//	
	//	if (isratioreal(lightnar, 12, 2))
	//	{
	//		std::vector<Point2f> points(4);
	//		roted_rect.points(&points[0]);
	//		//根据所得到的四点画线
	//		std::vector<std::vector<Point>> contors;
	//		contors.push_back(std::vector<Point>(points.begin(), points.end()));
	//		drawContours(drawract, contors, -1, Scalar(255, 0, 0), 2);
	//	}
	//}//查看灯条提取效果
	//imshow("try", drawcountours);
	//imshow("yuantu",gray);
	
		imshow("graw", test2);
		char c = (char)waitKey(1);
		if (c == 27)
			break;
	}
	return 0;
}

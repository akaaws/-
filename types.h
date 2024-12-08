#include<string.h>
#include<opencv2/opencv.hpp>
#include<math.h>
struct Lightbar
{
    std::string color;
    cv::Point2f center, top, bottom, left;
    std::vector<cv::Point2f> points;
    double angle, length, ratio,real_width;

    explicit Lightbar(const cv::RotatedRect& rotated_rect)
    {
        std::vector<cv::Point2f> points(4);
        rotated_rect.points(&points[0]);
        std::sort(points.begin(), points.end(), [](const cv::Point2f& a, const cv::Point2f& b) {
            return a.y < b.y;
            });

        this->center = rotated_rect.center;
        this->top = (points[0] + points[1]) / 2;
        this->bottom = (points[2] + points[3]) / 2;
        this->left = this->bottom - this->top;
        this->length = rotated_rect.size.height;
        this->real_width = rotated_rect.size.width * cos(rotated_rect.angle);
        if (rotated_rect.size.height >= rotated_rect.size.width)
        {
            this->ratio = rotated_rect.size.height / rotated_rect.size.width;
        }
        else
            this->ratio = rotated_rect.size.width / rotated_rect.size.height;
        this->points.emplace_back(this->top);
        this->points.emplace_back(this->bottom);

        auto width = cv::norm(points[0] - points[1]);
    }
};
//bool islengthreal(Lightbar a, double max, double min,double transmit)/*
//    return a.length/transmit <= max && a.length/transmit >= min;

//}*/
bool isratioreal(Lightbar b, float max, float min)
{
    return b.ratio <= max && b.ratio >= min;
}
struct Armor
{
    Lightbar left, right;
    double ratio;
    std::vector<cv::Point2f> points;
    cv::Mat partton;
    explicit Armor(const Lightbar& left, const Lightbar& right) :left(left), right(right)
    {
        this->points.emplace_back(left.top);
        this->points.emplace_back(left.bottom);
        this->points.emplace_back(right.top);
        this->points.emplace_back(right.bottom);
    }

    bool check_Armor()
    {
        double width, length, ratio;
        width = cv::norm(left.center - right.center);
        length = cv::norm(left.top - left.bottom);
        ratio = width / length;
        if (ratio < 2.9 && ratio>2.5)
            return true;
    }
};
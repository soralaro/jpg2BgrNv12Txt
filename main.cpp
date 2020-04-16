#include <iostream>
#include "opencv2/opencv.hpp"

int main(int argc, char **argv) {
    if(argc<3)
    {
        std::cout<<"path , nv12 or bgr "<<std::endl;
        return -1;
    }

    std::string  path=argv[1];
    std::string type=argv[2];
    cv::Mat mat = cv::imread(path);
    if(mat.empty())
    {
        std::cout<<"open file "<<path<<" fail!"<<std::endl;
        return  -1;
    }
    std::string output_file_name=std::to_string(mat.cols)+"x"+std::to_string(mat.rows);

    if(type.compare("bgr")==0)
    {
        output_file_name+="bgr.txt";
        FILE* output_file = fopen(output_file_name.c_str(), "wt");
        for(int row=0;row<mat.rows;row++)
        {
            for(int cols=0;cols<mat.cols;cols++)
            {
               std::string str_v=std::to_string(mat.at<cv::Vec3b>(row,cols)[0]);
               fprintf(output_file,"%s ",str_v.c_str());
               str_v=std::to_string(mat.at<cv::Vec3b>(row,cols)[1]);
               fprintf(output_file,"%s ",str_v.c_str());
               str_v=std::to_string(mat.at<cv::Vec3b>(row,cols)[2]);
               fprintf(output_file,"%s",str_v.c_str());
               if(cols!=mat.cols-1)
               {
                   fprintf(output_file," ");
               }else if(row!=mat.rows-1)
               {
                   fprintf(output_file,"\n");
               }
            }
        }
        fclose(output_file);
    }else if(type.compare("nv12")==0)
    {
        output_file_name+="nv12.txt";
        FILE* output_file = fopen(output_file_name.c_str(), "wt");
        cv::Mat yuv_mat(mat.rows*3/2,mat.cols,CV_8UC1);
        cv::cvtColor(mat,yuv_mat,cv::COLOR_BGR2YUV_IYUV);
        for(int row=0;row<mat.rows;row++)
        {
            //save Y
            for(int cols=0;cols<mat.cols;cols++)
            {
                std::string str_v=std::to_string(yuv_mat.at<uchar>(row,cols));
                fprintf(output_file,"%s",str_v.c_str());
                if(cols!=mat.cols-1)
                {
                    fprintf(output_file," ");
                }else
                {
                    fprintf(output_file,"\n");
                }
            }
        }
        for(int row=mat.rows;row<mat.rows*5/4;row++)
        {
            //save uv
            for(int cols=0;cols<mat.cols;cols++)
            {
                std::string str_v=std::to_string(yuv_mat.at<uchar>(row,cols));
                fprintf(output_file,"%s ",str_v.c_str());
                str_v=std::to_string(yuv_mat.at<uchar>(row+mat.rows/4,cols));
                fprintf(output_file,"%s",str_v.c_str());
                if(cols!=mat.cols/2-1&&cols!=mat.cols-1)
                {
                    fprintf(output_file," ");
                }else if(cols!=mat.cols-1||row!=mat.rows*5/4-1)
                {
                    fprintf(output_file,"\n");
                }
            }
        }
        fclose(output_file);

    }else
    {
        std::cout<<"output type must be bgr or nv12";
    }
    return 0;
}
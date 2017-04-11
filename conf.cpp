#ifndef _CONF_H
#define _CONF_H

/**
 *  Conf
 */

#include <iostream>
#include <string>
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/detail/autocalib.hpp"
#include "opencv2/stitching/detail/blenders.hpp"
#include "opencv2/stitching/detail/camera.hpp"
#include "opencv2/stitching/detail/exposure_compensate.hpp"
#include "opencv2/stitching/detail/matchers.hpp"
#include "opencv2/stitching/detail/motion_estimators.hpp"
#include "opencv2/stitching/detail/seam_finders.hpp"
#include "opencv2/stitching/detail/util.hpp"
#include "opencv2/stitching/detail/warpers.hpp"
#include "opencv2/stitching/warpers.hpp"
#include "helper.cpp"

using namespace std;
using namespace cv;
using namespace cv::detail;

namespace conf {

    vector<string> img_names;
    // 是否预览
    bool preview = false;
    // 是否器用GPU
    bool try_gpu = false;
    // 图像匹配分辨率（*100000）
    double work_megapix = 0.6;
    // 拼接缝隙大小
    double seam_megapix = 0.1;
    // 拼接分辨率
    double compose_megapix = -1;
    // 两幅图来自同一全景图置信度
    float conf_thresh = 1.f;
    // 特征检测算法：surf
    string features_type = "surf";
    // 特征点检测置信等级，最近邻匹配距离与次近邻匹配距离的比值
    float match_conf = 0.3f;
    // 光束平均法 (reproj|ray)
    string ba_cost_func = "ray";
    // mask
    string ba_refine_mask = "xxxxx";
    // 波形校正标志
    bool do_wave_correct = true;
    // 水平波形校正
    WaveCorrectKind wave_correct = detail::WAVE_CORRECT_HORIZ;
    // 将匹配的图形以点的形式保存到文件中
    bool save_graph = false;
    std::string save_graph_to;

    // 融合的平面（默认球星）
    string warp_type = "spherical";
    // 光照补偿方法
    int expos_comp_type = ExposureCompensator::GAIN_BLOCKS;
    // 缝隙估计方法
    string seam_find_type = "gc_color";
    int blend_type = Blender::MULTI_BAND;
    float blend_strength = 5;

    // 拼接结果文件名
    string result_name = "result.jpg";


    static int parseCmdArgs(int argc, char** argv)
    {
        if (argc == 1)
        {
            playArgumentError();
            return -1;
        }
        for (int i = 0; i < argc; ++i)
        {
            if (string(argv[i]) == "--help" || string(argv[i]) == "/?")
            {
                playArgumentError();
                return -1;
            }
            else if (string(argv[i]) == "--preview")
            {
                preview = true;
            }
            else if (string(argv[i]) == "--try_gpu")
            {
                if (string(argv[i + 1]) == "no")
                    try_gpu = false;
                else if (string(argv[i + 1]) == "yes")
                    try_gpu = true;
                else
                {
                    cout << "Bad --try_gpu flag value\n";
                    return -1;
                }
                i++;
            }
            else if (string(argv[i]) == "--work_megapix")
            {
                work_megapix = atof(argv[i + 1]);
                i++;
            }
            else if (string(argv[i]) == "--seam_megapix")
            {
                seam_megapix = atof(argv[i + 1]);
                i++;
            }
            else if (string(argv[i]) == "--compose_megapix")
            {
                compose_megapix = atof(argv[i + 1]);
                i++;
            }
            else if (string(argv[i]) == "--result")
            {
                result_name = argv[i + 1];
                i++;
            }
            else if (string(argv[i]) == "--match_conf")
            {
                match_conf = static_cast<float>(atof(argv[i + 1]));
                i++;
            }
            else if (string(argv[i]) == "--conf_thresh")
            {
                conf_thresh = static_cast<float>(atof(argv[i + 1]));
                i++;
            }
            else if (string(argv[i]) == "--ba")
            {
                ba_cost_func = argv[i + 1];
                i++;
            }
            else if (string(argv[i]) == "--ba_refine_mask")
            {
                ba_refine_mask = argv[i + 1];
                if (ba_refine_mask.size() != 5)
                {
                    cout << "Incorrect refinement mask length.\n";
                    return -1;
                }
                i++;
            }
            else if (string(argv[i]) == "--wave_correct")
            {
                if (string(argv[i + 1]) == "no")
                    do_wave_correct = false;
                else if (string(argv[i + 1]) == "horiz")
                {
                    do_wave_correct = true;
                    wave_correct = detail::WAVE_CORRECT_HORIZ;
                }
                else if (string(argv[i + 1]) == "vert")
                {
                    do_wave_correct = true;
                    wave_correct = detail::WAVE_CORRECT_VERT;
                }
                else
                {
                    cout << "Bad --wave_correct flag value\n";
                    return -1;
                }
                i++;
            }
            else if (string(argv[i]) == "--save_graph")
            {
                save_graph = true;
                save_graph_to = argv[i + 1];
                i++;
            }
            else if (string(argv[i]) == "--warp")
            {
                warp_type = string(argv[i + 1]);
                i++;
            }
            else if (string(argv[i]) == "--expos_comp")
            {
                if (string(argv[i + 1]) == "no")
                    expos_comp_type = ExposureCompensator::NO;
                else if (string(argv[i + 1]) == "gain")
                    expos_comp_type = ExposureCompensator::GAIN;
                else if (string(argv[i + 1]) == "gain_blocks")
                    expos_comp_type = ExposureCompensator::GAIN_BLOCKS;
                else
                {
                    cout << "Bad exposure compensation method\n";
                    return -1;
                }
                i++;
            }
            else if (string(argv[i]) == "--seam")
            {
                if (string(argv[i + 1]) == "no" ||
                    string(argv[i + 1]) == "voronoi" ||
                    string(argv[i + 1]) == "gc_color" ||
                    string(argv[i + 1]) == "gc_colorgrad" ||
                    string(argv[i + 1]) == "dp_color" ||
                    string(argv[i + 1]) == "dp_colorgrad")
                    seam_find_type = argv[i + 1];
                else
                {
                    cout << "Bad seam finding method\n";
                    return -1;
                }
                i++;
            }
            else if (string(argv[i]) == "--blend")
            {
                if (string(argv[i + 1]) == "no")
                    blend_type = Blender::NO;
                else if (string(argv[i + 1]) == "feather")
                    blend_type = Blender::FEATHER;
                else if (string(argv[i + 1]) == "multiband")
                    blend_type = Blender::MULTI_BAND;
                else
                {
                    cout << "Bad blending method\n";
                    return -1;
                }
                i++;
            }
            else if (string(argv[i]) == "--blend_strength")
            {
                blend_strength = static_cast<float>(atof(argv[i + 1]));
                i++;
            }
            else if (string(argv[i]) == "--output")
            {
                result_name = argv[i + 1];
                i++;
            }
            else
                img_names.push_back(argv[i]);
        }
        if (preview)
        {
            compose_megapix = 0.6;
        }
        return 0;
    }
}

#endif

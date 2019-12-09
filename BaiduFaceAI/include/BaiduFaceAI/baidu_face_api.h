#ifndef TESTFACEAPI_TESTFACEAPI_INCLUDE_BAIDU_FACE_API_H
#define TESTFACEAPI_TESTFACEAPI_INCLUDE_BAIDU_FACE_API_H

#include <string>
#include <vector>
#include "opencv2\opencv.hpp"

struct FaceInfo
{
    float mWidth;     // rectangle width
    float mAngle;     // rectangle tilt angle [-45 45] in degrees
    float mCenter_y;  // rectangle center y
    float mCenter_x;  // rectangle center x
    float mConf;
};
struct TrackFaceInfo
{
    TrackFaceInfo() {}

    FaceInfo box;
    std::vector<int> landmarks;
    float score;
    unsigned long face_id;
    std::vector<float> headPose;
};

struct QualityResult
{
    int face_num = -1;
    float bluriness = 0.7f; // < thr  ok
    int illumination = 40; // >= thr ok
    float occlusion[7] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 }; // < thr ok
    int occlusion_part = 50; // ignore
};

class  BaiduFaceApi
{
public:
	BaiduFaceApi();
	~BaiduFaceApi();
    // sdk ��ʼ��
	// id_cardĬ��Ϊfalse������Ϊtrue��ʾ��ȡ֤����ģʽ���ͷ�֤����ģʽ��������ֵ��ͨ��
	int sdk_init(bool id_card=false);
    // ��ѯ�Ƿ�ͨ����Ȩ
	bool is_auth();

	// ��ȡ�豸ָ��
	const char * get_device_id();
    // ��������
    const char* face_attr(const char* image, int img_type);
    // ��������(���������ͼƬbuf)
    const char* face_attr_by_buf(const unsigned char* image, int size);
    // ��������
    const char* face_quality(const char* image, int img_type);
    // ��������(���������ͼƬbuf)
    const char* face_quality_by_buf(const unsigned char* image, int size);
	//����ע��
	const char* user_add(const char* user_id, const char* group_id,
		const char* image, int img_type, const char* user_info = nullptr);
    //����ע��(���������ͼƬbuf)
    const char* user_add_by_buf(const char* user_id, const char* group_id,
        const unsigned char* image, int size, const char* user_info = nullptr);
	// ��������
	const char * user_update(const char* user_id, const char* group_id,
		const char * image, int img_type, const char* user_info = nullptr);
    // ��������(���������ͼƬbuf)
    const char * user_update_by_buf(const char* user_id, const char* group_id,
        const unsigned char* image, int size, const char* user_info = nullptr);
	// ����ɾ��
	const char * user_face_delete(const char* user_id, const char* group_id,
		const char* face_token);
	// �û�ɾ��
	const char * user_delete(const char* user_id, const char* group_id);
	// �����
	const char * group_add(const char* group_id);
	// ��ɾ��
	const char * group_delete(const char* group_id);
	// ��ѯ�û���Ϣ
	const char * get_user_info(const char*user_id, const char* group_id);
	// �û����б��ѯ
	const char * get_user_list(const char* group_id, int start = 0, int length = 100);
	// ���б��ѯ
	const char * get_group_list(int start = 0, int length = 100);
	// �����Ա�
	const char* match(const char* image1, int img_type1, const char* image2, \
		int img_type2);
    // �����Ա�
    const char* match_by_buf(const unsigned char* image1, int size1, const unsigned char* image2, \
        int size2);
    // �����Ա�(ͼƬ����Ƶ֡�Ա�)
    const char* match_by_img_and_frame(const char* image1, int img_type1, const cv::Mat &mat);
 // �����Ա�(����ֵ��ͼƬ�ȶ�)
    const char* match_by_feature(const std::vector<float>& f1, const char* image2, \
        int img_type2);
    // �����Ա�(����ֵ��ͼƬ������buffer�ȶ�)
    const char* match_by_feature(const std::vector<float>& f1, const unsigned char* image2, \
        int size);
    // ���������⵽�ڴ�
    bool load_db_face();
	// ����ʶ��
	const char* identify(const char* image, int img_type, const char* group_id_list, \
		const char* user_id, int user_top_num=1);
    // ����ʶ��(��������Ƚ�,��ǰ����)
    const char* identify(const char* image, int img_type, int user_top_num = 1);
	// ����ʶ��(����opencv��Ƶ֡)
    const char* identify(const cv::Mat &mat, const char* group_id_list, \
        const char* user_id, int user_top_num = 1);
    // ����ʶ��(����opencv��Ƶ֡)(��������Ƚϣ���ǰ����)
    const char* identify(const cv::Mat &mat, int user_top_num = 1);
    // ����ʶ��(���������ͼƬbuf)
    const char* identify_by_buf(const unsigned char* image, int size, const char* group_id_list, \
        const char* user_id, int user_top_num = 1);
    // ����ʶ��(���������ͼƬbuf)(��������Ƚϣ���ǰ����)
    const char* identify_by_buf(const unsigned char* image, int size, int user_top_num = 1);
    // ����ʶ��(��������ֵfeature)
    const char* identify_by_feature(const std::vector<float>& f1, const char* group_id_list, \
        const char* user_id, int user_top_num = 1);

    // ����ʶ��(��������ֵfeature)(��������Ƚϣ���ǰ����)
    const char* identify_by_feature(const std::vector<float>& f1, int user_top_num = 1);
    
	//����Ϊ�ɼ���������
	// �����Ƿ�ִ��������⣬Ĭ��Ϊfalse
	void set_isCheckQuality(bool flag = false);
	// ������ֵ��ȡֵ��Χ0~255��Ĭ��40��Խ���������Խ��
	void set_illum_thr(float thr = 40);
	// ģ����ֵ��ȡֵ��Χ0~1��Ĭ��0.7��ԽС����ͼ��Խ����
	// ������Ϊ1ʱ��ģ����ⲻ�����ҽ����ͨ����������Ϊ0ʱ��ģ����ⲻ�����ҽ��ͨ��
	void set_blur_thr(float thr = 0.7);
	// ���ۡ����ۡ����ӡ���͡������ա������ա��°͵��ڵ���ֵ��ȡֵ��Χ0~1��Ĭ��0.5��ֵԽС�����ڵ�����ԽС
	// ������Ϊ1ʱ���ڵ���ⲻ�����ҽ����ͨ����������Ϊ0ʱ���ڵ���ⲻ�����ҽ��ͨ��
	void set_occlu_thr(float thr = 0.5);
	// ����pitch��yaw��roll�ȽǶȵ���ֵ��Ĭ�϶�Ϊ15&deg;��Խ�����ɲɼ��������Ƕ�Խ�󣬵��ǽǶ�Խ��ʶ��Ч����Խ��
	void set_eulur_angle_thr(int pitch_thr = 15, int yaw_thr = 15, int roll_thr = 15);

	// �����������Ŷ���ֵ��ȡֵ��Χ0~1��ȡ0����Ϊ���м������Ľ������������Ĭ��0.5
	void set_notFace_thr(float thr = 0.5);
	// ��С�����ߴ磺��Ҫ��⵽����С�����ߴ磬������Ҫ��⵽30*30������������Ϊ30��
	// �óߴ�ռͼ�����ԽС�����ٶ�Խ����������ο�����ָ���½ڡ�Ĭ��ֵ30
	void set_min_face_size(int size = 30);
	// ���ٵ�Ŀ���ִ�м���ʱ��������λ���룬Ĭ��300��ֵԽСԽ����췢����Ŀ�꣬����cpuռ���ʻ���ߡ������ٶȱ���
	void set_track_by_detection_interval(int interval_in_ms = 300);
	// δ���ٵ�Ŀ��ʱ�ļ��������λ���룬Ĭ��300��ֵԽСԽ�췢����Ŀ�꣬����cpuռ���ʻ���ߡ������ٶȱ���
	void set_detect_in_video_interval(int interval_in_ms = 300);
	
    /*
    * std::vector<TrackFaceInfo> *& out:�����ļ���������Ϣ
    * const char* img  : Input img,1 is base64 img, 2 is file path
    * int imgType : Input img's coding type ,1 is base64 img, 2 is file path
    * int maxTrackObjNum: ���Ҫtracking��������������Ϊ1��ֻtrackingһ���ˣ��������Ϊ3�����tracking 3���ˡ�
    * return Ϊ���صļ����������
    */
    int track(std::vector<TrackFaceInfo> *& out, const char* image, int img_type, int maxTrackObjNum);

	int track(std::vector<TrackFaceInfo> *& out,const cv::Mat &mat, int maxTrackObjNum);
    // ������⣨���������ͼƬbuf��
    int track_by_buf(std::vector<TrackFaceInfo> *& out, const unsigned char* image, int size, int maxTrackObjNum);

    // ֻ�����������������ͬtrack
    int track_max_face(std::vector<TrackFaceInfo> *& out, const char* image, int img_type);
    int track_max_face(std::vector<TrackFaceInfo> *& out, const cv::Mat &mat);
    // ���������⣨���������ͼƬbuf��
    int track_max_face_by_buf(std::vector<TrackFaceInfo> *& out, const unsigned char* image, int size);
	//����Ѹ��ٵ���������Ϣ
	void clearTrackedFaces();


    //����IR��Ĭ������
    const char* ir_liveness_check(const char* image, int img_type);
    //����IR��Ĭ������(����opencv����Ƶ֡)
    const char* ir_liveness_check(const cv::Mat& mat);
    //����IR��Ĭ�����⣨���������ͼƬbuf��
    const char* ir_liveness_check_by_buf(const unsigned char* image, int size);
    //��ĿRGB����������
    const char* rgb_liveness_check(const char* image, int img_type);
    //��ĿRGB����������(����opencv����Ƶ֡)
    const char* rgb_liveness_check(const cv::Mat& mat);
    //��ĿRGB���������⣨���������ͼƬbuf��
    const char* rgb_liveness_check_by_buf(const unsigned char* image, int size);

    //˫ĿRGB��IR���������⣨���������ͼƬbuf��
    const char* rgb_ir_liveness_check_by_buf(const unsigned char* rgb_img, int rgb_size
        , const unsigned char* ir_img, int ir_size);
    //˫ĿRGB��IR����������(����opencv����Ƶ֡)
    const char* rgb_ir_liveness_check(const cv::Mat& rgb_mat, const cv::Mat&ir_mat,
        float &rgb_score, float &ir_score);
    //˫Ŀ���(depth)���������⣨���������ͼƬbuf��
    const char* rgb_depth_liveness_check_by_buf(const unsigned char* rgb_img, int rgb_size
        , const unsigned char* depth_img, int depth_size);

    //˫ĿRGB��depth����������(����opencv����Ƶ֡)
    const char* rgb_depth_liveness_check(const cv::Mat& rgb_mat, const cv::Mat&depth_mat,
        float &rgb_score, float &depth_score);
	
    //��ȡ��⵽��������Ϣ������intΪ��������
    int get_tracked_faces(std::vector<TrackFaceInfo> *& vec);

    //��ȡ��������ֵ(����ͼƬ)
    int get_face_feature(const char* image, int img_type, const float*& feature);
    //��ȡ��������ֵ(����opencv��Ƶ֡)
    int get_face_feature(const cv::Mat& mat, const float*& feature);
    // //��ȡ��������ֵ(���������ͼƬbuf)
    int get_face_feature_by_buf(const unsigned char* image, int size,
        const float*& feature);
    //����ֵ�ȶ�
    float compare_feature(const std::vector<float>& f1, const std::vector<float>& f2);
private:
	std::string m_res;
	bool m_is_tool = false;
    std::vector<TrackFaceInfo> m_tracked_faces;
	
};
#endif


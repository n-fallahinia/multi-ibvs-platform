#include "Servo.h"

Servo::Servo(const CameraMatrix &cam_params, int num_points, bool opt_adaptive): 
    m_cam_px(cam_params.px),
    m_cam_py(cam_params.py),
    m_cam_u0(cam_params.u0),
    m_cam_v0(cam_params.v0),
    m_num_points(num_points)
{   
    p.resize(num_points);
    pd.resize(num_points);
    v_c.resize(6); //6 dof velocity

    task.setServo(vpServo::EYEINHAND_CAMERA);
    task.setInteractionMatrixType(vpServo::CURRENT);
    if (opt_adaptive){
        vpAdaptiveGain lambda(4, 0.4, 30); 
        task.setLambda(lambda);
    }
    else{
       task.setLambda(0.5);
    }

    for (size_t i = 0; i < m_num_points; i++)
    {
        task.addFeature(p[i], pd[i]);
    }
    // set the initial velocity to zero
    v.vx = 0;
    v.vy = 0;
    v.vz = 0;
    v.wx = 0;
    v.wy = 0;
    v.wz = 0;
    std::cout<<"log::Servo()"<<std::endl;
};

Servo::Servo(){
    std::cout<<"log::Servo()"<<std::endl;
}

Servo::~Servo(){
    std::cout<<"log::~Servo()"<<std::endl;
}

void Servo::loadCamera(){    
    cam.initPersProjWithoutDistortion(m_cam_px, m_cam_py, m_cam_u0, m_cam_v0); 
    std::cout<<"camera intrinsic loaded"<<std::endl;
};

void Servo::setServo(){

}

void Servo::setDepth(double depth){
    m_des_depth = depth;
}

void Servo::setDesiredView(const std::vector<vpImagePoint> &des_corners){
    for (size_t i = 0; i < des_corners.size(); i++)
    {
        vpFeatureBuilder::create(pd[i], cam, des_corners[i]);
        pd[i].set_Z(m_des_depth);

        std::cout<<"\tpoint "<<i<< " added"<< std::endl;
    }
}

void Servo::updateFeatures(const std::vector<vpImagePoint> &corners){
    for (size_t i = 0; i < corners.size(); i++)
    {
        vpFeatureBuilder::create(p[i], cam, corners[i]);
        p[i].set_Z(m_des_depth);
    }
}

double Servo::getError() {
    m_error = task.getError().sumSquare();
    return m_error;
}

CameraVelocity Servo::getVelocity() {
    v_c = task.computeControlLaw();
    v.vx = v_c[0];
    v.vy = v_c[1];
    v.vz = v_c[2];
    v.wx = v_c[3];
    v.wy = v_c[4];
    v.wz = v_c[5];
    return v;
}

std::unique_ptr<Servo> Servo::create(const CameraMatrix &cam_params, int num_points, bool opt_adaptive){
    return std::unique_ptr<Servo>(new Servo(cam_params, num_points, opt_adaptive));
}
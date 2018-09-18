class RealSense
{
public:
    RealSense ();
    ~RealSense ();

    std::shared_ptr<rs2::pipeline> pipe = std::make_shared<rs2::pipeline>();

    
    //auto pipe = std::make_shared<rs2::pipeline>();

};

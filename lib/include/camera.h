class Camera
    {
    private:
        MATHS::N3 position;
        int yaw = 0;
        int pitch = 0;
        int fov;

    public:
        Camera(int fov);
        ~Camera();

        void rotate(int delta_yaw, int delta_pitch);
        void move(MATHS::N3 delta_position);
        MATHS::N3 get_position() const { return position; }
    };
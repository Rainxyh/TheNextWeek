class image_texture : public texture
{
public:
    unsigned char *data;
    int nx, ny, nn;

    image_texture() {}
    image_texture(unsigned char *pixels, int nx, int ny, int nn) : data(pixels), nx(nx), ny(ny), nn(nn) {}

    //输入u和v，输出对应图片像素的rgb值
    virtual vec::vec3 value(float u, float v, const vec::vec3 &p) const
    {
        int i = int((u)*nx); //求出像素索引
        int j = int((1 - v) * ny - 0.001f);
        if (i < 0)
            i = 0;
        if (j < 0)
            j = 0;
        if (i > nx - 1)
            i = nx - 1;
        if (j > ny - 1)
            j = ny - 1;
        float r = int(data[nn * (i + nx * j)]) / 255.0f;
        float g = int(data[nn * (i + nx * j) + 1]) / 255.0f;
        float b = int(data[nn * (i + nx * j) + 2]) / 255.0f;
        return vec::vec3(r, g, b);
    }

    virtual const image_texture* get_class_type(void) const override{
        return this;
    }
};

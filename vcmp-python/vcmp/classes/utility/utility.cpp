#include "utility.h"
#include "../core.h"

const std::string Vector::to_string() {
    std::string out;
    out = "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z) + ")";

    return static_cast<pybind11::str>(out);
}

const std::string Quaternion::to_string() {
    std::string out;
    out = "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z) + ", " + std::to_string(this->w) + ")";

    return static_cast<pybind11::str>(out);
}

float Vector::Length(void) const { return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)); }
float Vector::Distance(const Vector& v) const { return sqrt(pow(this->x - v.x, 2) + pow(this->y - v.y, 2) + pow(this->z - v.z, 2)); }
float Vector::Dot(const Vector& v) { return (this->x * v.x) + (this->y * v.y) + (this->z * v.z); }
Vector& Vector::Normalize(void)
{
    float invLen = 1.0f / this->Length();
    this->x *= invLen;
    this->y *= invLen;
    this->z *= invLen;
    return *this;
}

bool Vector::operator==(const Vector& v) const { return this->x == v.x && this->y == v.y && this->z == v.z; }
Vector Vector::operator-(void) const { return Vector(-x, -y, -z); }
Vector Vector::operator+(const Vector& v) const { return Vector(this->x + v.x, this->y + v.y, this->z + v.z); }
Vector Vector::operator-(const Vector& v) const { return Vector(this->x - v.x, this->y - v.y, this->z - v.z); }
Vector Vector::operator*(const float f) const { return Vector(this->x * f, this->y * f, this->z * f); }
Vector Vector::operator/(const float f) const { return Vector(this->x / f, this->y / f, this->z / f); }
Vector& Vector::operator=(const Vector& v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    return *this;
}
Vector& Vector::operator=(const float f)
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = f;
    return *this;
}

bool Quaternion::operator==(const Quaternion& q) const { return this->w == q.w && this->x == q.x && this->y == q.y && this->z == q.z; }
Quaternion Quaternion::operator-(void) const { return Quaternion(-w, -x, -y, -z); }
Quaternion Quaternion::operator+(const Quaternion& q) const { return Quaternion(this->w + q.w, this->x + q.x, this->y + q.y, this->z + q.z); }
Quaternion Quaternion::operator-(const Quaternion& q) const { return Quaternion(this->w - q.w, this->x - q.x, this->y - q.y, this->z - q.z); }
Quaternion Quaternion::operator*(const float f) const { return Quaternion(this->w * f, this->x * f, this->y * f, this->z * f); }
Quaternion Quaternion::operator/(const float f) const { return Quaternion(this->w / f, this->x / f, this->y / f, this->z / f); }
Quaternion& Quaternion::operator=(const Quaternion& q)
{
    this->w = q.w;
    this->x = q.x;
    this->y = q.y;
    this->z = q.z;
    return *this;
}
Quaternion& Quaternion::operator=(const float q)
{
    this->w = 0.0f;
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = q;
    return *this;
}

unsigned int RGBa::toUInt() { 
    return this->r << 24 | this->g << 16 | this->b << 8 | this->a;
}

const pybind11::str RGBa::to_string() {
    pybind11::str ret = "(" + std::to_string(this->r) + ", " + std::to_string(this->g) + ", " + std::to_string(this->b) + ", " + std::to_string(this->a) + ")";
    return ret;
}

unsigned int cRGB::toUInt() { 
    return this->r << 16 | this->g << 8 | this->b;
}

const pybind11::str cRGB::to_string() {
    pybind11::str ret = "(" + std::to_string(this->r) + ", " + std::to_string(this->g) + ", " + std::to_string(this->b) + ")";
    return ret;
}

PYBIND11_EMBEDDED_MODULE(vcmp_utility, m) {
    pybind11::class_<RGBa, std::shared_ptr<RGBa> >(m, "RGBA")
        .def(pybind11::init<int, int, int, int>())
        .def_readwrite("r", &RGBa::r)
        .def_readwrite("g", &RGBa::g)
        .def_readwrite("b", &RGBa::b)
        .def_readwrite("a", &RGBa::a)
        .def("__repr__", &RGBa::to_string);

    pybind11::class_<cRGB, std::shared_ptr<cRGB> >(m, "RGB")
        .def(pybind11::init<int, int, int>())
        .def_readwrite("r", &cRGB::r)
        .def_readwrite("g", &cRGB::g)
        .def_readwrite("b", &cRGB::b)
        .def("__repr__", &cRGB::to_string);

    pybind11::class_<Vector, std::shared_ptr<Vector> >(m, "Vector")
        .def(pybind11::init<float, float, float>())
        .def_readwrite("x", &Vector::x)
        .def_readwrite("y", &Vector::y)
        .def_readwrite("z", &Vector::z)
        .def_readwrite("X", &Vector::x)
        .def_readwrite("Y", &Vector::y)
        .def_readwrite("Z", &Vector::z)
        .def("__add__", &Vector::operator+)
        .def("__mul__", &Vector::operator*)
        .def("__div__", &Vector::operator/)
        .def<Vector(Vector::*)(void) const>("__unm__", &Vector::operator-)
        .def<Vector(Vector::*)(const Vector&) const>("__sub__", &Vector::operator-)
        .def("__repr__", &Vector::to_string);

    pybind11::class_<Quaternion, std::shared_ptr<Quaternion> >(m, "Quaternion")
        .def(pybind11::init<float, float, float, float>())
        .def_readwrite("x", &Quaternion::x)
        .def_readwrite("y", &Quaternion::y)
        .def_readwrite("z", &Quaternion::z)
        .def_readwrite("w", &Quaternion::w)
        .def_readwrite("X", &Quaternion::x)
        .def_readwrite("Y", &Quaternion::y)
        .def_readwrite("Z", &Quaternion::z)
        .def_readwrite("W", &Quaternion::w)
        .def("__add__", &Quaternion::operator+)
        .def("__mul__", &Quaternion::operator*)
        .def("__div__", &Quaternion::operator/)
        .def<Quaternion(Quaternion::*)(void) const>("__unm__", &Quaternion::operator-)
        .def<Quaternion(Quaternion::*)(const Quaternion&) const>("__sub__", &Quaternion::operator-)
        .def("__repr__", &Quaternion::to_string);


    pybind11::class_<WastedSettings, std::shared_ptr<WastedSettings> >(m, "WastedSettings")
        .def(pybind11::init<int, int, float, float, cRGB, int, int>())
        .def_readonly("death_time", &WastedSettings::deathTime)
        .def_readonly("fade_time", &WastedSettings::fadeTime)
        .def_readonly("fade_in_speed", &WastedSettings::fadeInSpeed)
        .def_readonly("fade_out_speed", &WastedSettings::fadeOutSpeed)
        .def_readonly("fade_colour", &WastedSettings::fadeColour)
        .def_readonly("corpse_delay", &WastedSettings::corpseFadeDelay)
        .def_readonly("corpse_fade_time", &WastedSettings::corpseFadeTime);

    pybind11::class_<Bounds, std::shared_ptr<Bounds> >(m, "BoundsSettings")
        .def(pybind11::init<float, float, float, float>())
        .def_readonly("max_x", &Bounds::maxX)
        .def_readonly("min_x", &Bounds::minX)
        .def_readonly("max_y", &Bounds::maxY)
        .def_readonly("min_y", &Bounds::minY);
}
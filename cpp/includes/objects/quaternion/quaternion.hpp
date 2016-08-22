#ifndef RAPP_OBJECT_QUATERNION
#define RAPP_OBJECT_QUATERNION
#include "includes.ihh"
namespace rapp {
namespace object {

/**
 * \struct quaternion
 * \brief class which encapsulate quaternion vector
 * \version 0.7.0
 * \date 19 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
struct quaternion
{
    /**
     * \brief Consruct using code coordinates (x,y,z,w)
     * \param x is quaternion x component
     * \param y is quaternion y component
     * \param z is quaternion z component
     * \param w is quaternion w (NOTE: angle theta?)
     */
	quaternion(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w)
    {}
    
    /// \brief empty consructor
    quaternion() = default;
    
    /// \brief copy constructor
    quaternion(const rapp::object::quaternion &) = default;

	quaternion(const rapidjson::Value::ConstMemberIterator & iter)
    {
        auto it_x = iter->FindMember("x");
        if (it_x != iter->MemberEnd()) {
            if (it_x->value.IsDouble())
            {
                this->x = it_x->value.GetDouble();
            }
            else
                throw std::runtime_error("member `x` not a float");    
        }
        else 
            throw std::runtime_error("param has no `x` value");

        auto it_y = iter->FindMember("y");
        if (it_y != iter->MemberEnd()) {
            if (it_y->value.IsDouble())
            {
                this->y = it_y->value.GetDouble();
            }
            else
                throw std::runtime_error("member `y` not a float");    
        }
        else 
            throw std::runtime_error("param has no `y` value");

        auto it_z = iter->FindMember("z");
        if (it_z != iter->MemberEnd()) {
            if (it_z->value.IsDouble())
            {
                this->z = it_z->value.GetDouble();
            }
            else
                throw std::runtime_error("member `z` not a float");    
        }
        else 
            throw std::runtime_error("param has no `z` value");

        auto it_w = iter->FindMember("w");
        if (it_w != iter->MemberEnd()) {
            if (it_w->value.IsDouble())
            {
               this->w = it_w->value.GetDouble();
            }
            else
                throw std::runtime_error("member `w` not a float");    
        }
        else 
            throw std::runtime_error("param has no `w` value");
    }
    
    /// \brief equalit-> operator
    bool operator==(const rapp::object::quaternion & rhs) const
    {
		return (this->x == rhs.x) &&
			   (this->y == rhs.y) && 
			   (this->z == rhs.z) &&
			   (this->w == rhs.w);
    }

	template <typename W>
    void Serialize(W & writer) const
    {
        writer.StartObject();
        writer.String("x");
        writer.Double(x);
        writer.String("y");
        writer.Double(y);
        writer.String("z");
        writer.Double(z);
        writer.String("w");
        writer.Double(w);
        writer.EndObject();

    }
    
	/// members
	float x = 0;
    float y = 0;
    float z = 0;
    float w = 1;
};
}
}
#endif

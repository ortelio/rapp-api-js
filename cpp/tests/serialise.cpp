/**
 * \note test json serialization of objects
 * \warning not a unit test!
 */
#include "objects.hpp"
#include <ctime>
#include <chrono>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

///
///
int main(int argc, char * argv[])
{
    /// we need a class/factory for timestamps
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    auto eta = now.time_since_epoch();

    /// a time stamp (why both seconds and nanoseconds)
    /// WARNING implicit casting is VERY DANGEROUS
    rapp::object::time t(std::chrono::duration_cast<std::chrono::seconds>(eta).count(),
                         std::chrono::duration_cast<std::chrono::nanoseconds>(eta).count());

    /// a header: sequence, timestap, frameid
    rapp::object::header meta(0, t, "/map/blahblah");
    /// robot position
    rapp::object::point position(0.0, 0.0, 1.0);
    /// robot quaternion (orientation)
    rapp::object::quaternion quat(0.0, 0.0, 1.0, 0.4);
    /// robot pose
    rapp::object::pose pose(position, quat);
    /// robot pose_stamped
    rapp::object::pose_stamped ps(meta, pose);

    std::cout << t.sec << " - " << t.nsec << "\r\n";

    //TEST JSON serialisation
    boost::property_tree::ptree tree;
    tree.add_child("start", ps.treefy());
    boost::property_tree::json_parser::write_json("test_serialise.json", tree);

    return 0;
}
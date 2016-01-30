#include "../includes/service/service_controller/service_controller.hpp"
#include "../includes/cloud/ontology_subclasses_of/ontology_subclasses_of.hpp"
#include "../includes/cloud/ontology_superclasses_of/ontology_superclasses_of.hpp"
#include <iostream>
///
/// query subclasses and superclass of of argv[1]
///
int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        std::cout << "query sub/super classes of: " << argv[1] << std::endl;
        std::string query = argv[1];
        // Service Controller 
        rapp::services::service_controller ctrl;
        // Subclass Ontologies callback
        auto sb_cb = [](std::vector<std::string> classes)
                     { 
                        for (const auto & str : classes)
                            std::cout << str << std::endl;
                     };
        // the caller object
        auto sub_call = std::make_shared<rapp::cloud::ontology_subclasses_of>(query, sb_cb);
        // Superclass Ontologies
        auto sp_cb = [](std::vector<std::string> classes)
                     {
                        for (const auto & str : classes)
                            std::cout << str << std::endl;
                     };
        // the caller
        auto super_call = std::make_shared<rapp::cloud::ontology_superclasses_of>(query, sp_cb);
        // Request from service controller to run this job
        ctrl.run_job(sub_call);
        ctrl.run_job(super_call);
        return 0;
    }
}

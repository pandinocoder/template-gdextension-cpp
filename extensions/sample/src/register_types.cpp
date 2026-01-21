#include "register_types.h"

#include "sample_node_2d.h"
#include "sample_ref_counted.h"

#include <godot/print.h>
#include <godot/stl.h>

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

namespace sample {
    void initialize_extension(ModuleInitializationLevel p_level) {
        ::godot::fprint("initialize_extension(%d)", p_level);

        if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
        }

        ::godot::fprint("Initializing libsample GDExtension...");

        GDREGISTER_CLASS(SampleNode2D);
        // GDREGISTER_CLASS(SampleRefCounted);

        ::godot::fprint("Initialized libsample GDExtension.");
    }

    void destroy_extension(ModuleInitializationLevel p_level) {
        ::godot::fprint("destroy_extension(%d)", p_level);

        if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
        }

        ::godot::fprint("Destroying libsample GDExtension...");

        ::godot::fprint("Destroyed libsample GDExtension...");
    }
}

using namespace sample;

extern "C" {
    // Initialization.
    GDExtensionBool GDE_EXPORT sample_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_extension);
        init_obj.register_terminator(destroy_extension);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
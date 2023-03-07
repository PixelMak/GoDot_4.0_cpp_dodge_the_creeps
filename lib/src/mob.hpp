#ifndef GDEXTENSION_MOB_HPP
#define GDEXTENSION_MOB_HPP

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace game_lib
{
  using namespace godot;

  class Mob : public RigidBody2D 
  {
    GDCLASS(Mob, RigidBody2D)

    godot::AnimatedSprite2D* _animated_sprite;

  protected:
    static void _bind_methods();

  public:
    void _init() {}
    void _ready();
    void _on_VisibilityNotifier2D_screen_exited();
  };
} // namespace game_lib

#endif // GDEXTENSIONTEST_TEST_MOB_HPP

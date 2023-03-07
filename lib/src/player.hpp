#ifndef GDEXTENSION_PLAYER_HPP
#define GDEXTENSION_PLAYER_HPP

#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/input.hpp>

namespace game_lib
{
  using namespace godot;

  class Player : public Area2D
  {
    GDCLASS(Player, Area2D)

    godot::AnimatedSprite2D* _animated_sprite;
    godot::CollisionShape2D* _collision_shape;
    godot::Input* _inputs;
    godot::Vector2 _screen_size; // Size of the game window.

  protected:
    static void _bind_methods();

  public:
    real_t speed = 400; // How fast the player will move (pixels/sec).

    void _init() {}
    void _ready();
    void _process(const double p_delta);
    void start(const godot::Vector2 p_position);
    void _on_Player_body_entered(godot::Node2D* _body);
  };

}  // namespace game_lib

#endif // GDEXTENSIONTEST_TEST_Player_HPP
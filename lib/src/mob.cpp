#include "mob.hpp"
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>

namespace game_lib
{
  void Mob::_bind_methods()
  {
    godot::ClassDB::bind_method(godot::D_METHOD("_on_VisibilityNotifier2D_screen_exited"), &Mob::_on_VisibilityNotifier2D_screen_exited);
  }
  void game_lib::Mob::_ready()
  {
    RandomNumberGenerator random;
    random.randomize();
    _animated_sprite = get_node<godot::AnimatedSprite2D>("AnimatedSprite2D");
    _animated_sprite->play();
    godot::PackedStringArray mob_types = _animated_sprite->get_sprite_frames()->get_animation_names();
    _animated_sprite->set_animation(mob_types[random.randi() % mob_types.size()]);
  }

  void game_lib::Mob::_on_VisibilityNotifier2D_screen_exited()
  {
    queue_free();
  }
}

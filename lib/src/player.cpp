#include "player.hpp"
#include <godot_cpp/variant/utility_functions.hpp>

namespace game_lib
{
  void game_lib::Player::_bind_methods()
  {
    // Bind a method to this class.
    godot::ClassDB::add_signal("Player", godot::MethodInfo("hit"));
    godot::ClassDB::bind_method(godot::D_METHOD("_on_Player_body_entered"), &Player::_on_Player_body_entered);
  }

  void Player::_ready()
  {
    _animated_sprite = get_node<godot::AnimatedSprite2D>("AnimatedSprite2D");
    _collision_shape = get_node<godot::CollisionShape2D>("CollisionShape2D");
    _inputs = godot::Input::get_singleton();
    _screen_size = get_viewport_rect().size;
    hide();
  }

  void Player::_process(const double p_delta)
  {
    godot::Vector2 velocity(0, 0);

    velocity.x = _inputs->get_action_strength("ui_right") - _inputs->get_action_strength("ui_left");
    velocity.y = _inputs->get_action_strength("ui_down") - _inputs->get_action_strength("ui_up");

    if (velocity.length() > 0) {
      velocity = velocity.normalized() * speed;
      _animated_sprite->play();
    }
    else {
      _animated_sprite->stop();
    }

    godot::Vector2 position = get_position();
    position += velocity * (real_t)p_delta;
    position.x = godot::Math::clamp(position.x, (real_t)0.0, _screen_size.x);
    position.y = godot::Math::clamp(position.y, (real_t)0.0, _screen_size.y);
    set_position(position);

    if (velocity.x != 0) {
      _animated_sprite->set_animation("walk");
      _animated_sprite->set_flip_v(false);
      // See the note below about boolean assignment.
      _animated_sprite->set_flip_h(velocity.x < 0);
    }
    else if (velocity.y != 0) {
      _animated_sprite->set_animation("up");
      _animated_sprite->set_flip_v(velocity.y > 0);
    }
  }

  void Player::start(const godot::Vector2 p_position)
  {
    set_position(p_position);
    show();
    _collision_shape->set_disabled(false);
  }

  void Player::_on_Player_body_entered(godot::Node2D* _body)
  {
    hide(); // Player disappears after being hit.
    emit_signal("hit");
    // Must be deferred as we can't change physics properties on a physics callback.
    _collision_shape->set_deferred("disabled", true);
  }

}

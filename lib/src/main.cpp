#include "main.hpp"

namespace game_lib
{
  void game_lib::Main::_bind_methods()
  {
    godot::ClassDB::bind_method(godot::D_METHOD("set_mob_scene", "p_mob_scene"), &Main::set_mob_scene);
    godot::ClassDB::bind_method(godot::D_METHOD("get_mob_scene"), &Main::get_mob_scene);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mob_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"),
      "set_mob_scene", "get_mob_scene");

    godot::ClassDB::bind_method(godot::D_METHOD("game_over"), &Main::game_over);
    godot::ClassDB::bind_method(godot::D_METHOD("new_game"), &Main::new_game);
    godot::ClassDB::bind_method(godot::D_METHOD("_on_MobTimer_timeout"), &Main::_on_MobTimer_timeout);
    godot::ClassDB::bind_method(godot::D_METHOD("_on_ScoreTimer_timeout"), &Main::_on_ScoreTimer_timeout);
    godot::ClassDB::bind_method(godot::D_METHOD("_on_StartTimer_timeout"), &Main::_on_StartTimer_timeout);
  }

  Ref<PackedScene> Main::get_mob_scene()
  {
    return mob_scene;
  }

  void Main::set_mob_scene(Ref<PackedScene> p_mob_scene)
  {
    mob_scene = p_mob_scene;
  }

  void Main::_ready()
  {
    _hud = get_node<HUD>("HUD");
    _player = get_node<Player>("Player");
    _start_position = get_node<godot::Node2D>("StartPosition");
    _mob_spawn_location = get_node<godot::PathFollow2D>("MobPath/MobSpawnLocation");
    _mob_timer = get_node<godot::Timer>("MobTimer");
    _score_timer = get_node<godot::Timer>("ScoreTimer");
    _start_timer = get_node<godot::Timer>("StartTimer");
    // Uncomment these after adding the nodes in the "Sound effects" section of "Finishing up".
    _music = get_node<godot::AudioStreamPlayer>("Music");
    _death_sound = get_node<godot::AudioStreamPlayer>("DeathSound");
    RandomNumberGenerator* rand = new RandomNumberGenerator;
    _random = Ref<RandomNumberGenerator>(rand);
    _random->randomize();
  }
  void Main::game_over()
  {
    _hud->show_game_over();
    _score_timer->stop();
    _mob_timer->stop();
    _music->stop();
    _death_sound->play();
  }
  void Main::new_game()
  {
    score = 0;
    _hud->update_score(score);
    _hud->show_get_ready();
    _player->start(_start_position->get_position());
    get_tree()->call_group("mobs", "queue_free");
    _music->play();
    _start_timer->start();
  }
  void Main::_on_MobTimer_timeout()
  {
    // Create a new instance of the Mob scene.
    godot::Node* mob = mob_scene->instantiate();

    // Choose a random location on Path2D.
    _mob_spawn_location->set_progress((real_t)_random->randi());

    // Set the mob's direction perpendicular to the path direction.
    real_t direction = _mob_spawn_location->get_rotation() + (real_t)Math_PI / 2;

    // Set the mob's position to a random location.
    mob->set("position", _mob_spawn_location->get_global_position());

    // Add some randomness to the direction.
    direction += _random->randf_range((real_t)-Math_PI / 4, (real_t)Math_PI / 4);
    mob->set("rotation", direction);

    // Choose the velocity for the mob.
    godot::Vector2 velocity = godot::Vector2(_random->randf_range(150.0, 250.0), 0.0);
    mob->set("linear_velocity", velocity.rotated(direction));

    // Spawn the mob by adding it to the Main scene.
    add_child(mob);
  }
  void Main::_on_ScoreTimer_timeout()
  {   
    score += 1;
    _hud->update_score(score);
  }
  void Main::_on_StartTimer_timeout()
  {
    _mob_timer->start();
    _score_timer->start();
  }
}
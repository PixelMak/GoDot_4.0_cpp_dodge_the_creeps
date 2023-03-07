#ifndef GDEXTENSION_MAIN_HPP
#define GDEXTENSION_MAIN_HPP

#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/path_follow2d.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/object.hpp>

#include "hud.hpp"
#include "player.hpp"
#include "mob.hpp"

namespace game_lib
{
  using namespace godot;

  class Main : public Node
  {
    GDCLASS(Main, Node)

    int score;
    HUD* _hud;
    Player* _player;
    Node2D* _start_position;
    PathFollow2D* _mob_spawn_location;
    Timer* _mob_timer;
    Timer* _score_timer;
    Timer* _start_timer;
    AudioStreamPlayer* _music;
    AudioStreamPlayer* _death_sound;
    Ref<godot::RandomNumberGenerator> _random;

  protected:
    static void _bind_methods();

  public:
    godot::Ref<godot::PackedScene> mob_scene;

    Ref<PackedScene> get_mob_scene();
    virtual void set_mob_scene(Ref<PackedScene> p_mob_scene);

    void _ready();
    void game_over();
    void new_game();
    void _on_MobTimer_timeout();
    void _on_ScoreTimer_timeout();
    void _on_StartTimer_timeout();
  };
}

#endif // GDEXTENSION_MAIN_HPP
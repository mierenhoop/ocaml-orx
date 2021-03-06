module Status : sig
  type 'ok result = ('ok, [ `Orx ]) Stdlib.result
  type t = unit result

  val ok : t
  val error : t

  val open_error : 'ok result -> ('ok, [> `Orx ]) Stdlib.result
end

module Color : sig
  type t
end

module String_id : sig
  type t

  val undefined : t

  val get_id : string -> t

  val get_from_id : t -> string
end

module Structure : sig
  type t

  type guid
end

module Vector : sig
  type t

  val equal : t -> t -> bool

  val get_x : t -> float

  val get_y : t -> float

  val get_z : t -> float

  val get_size : t -> float

  val make : x:float -> y:float -> z:float -> t

  val set_x : t -> float -> unit

  val set_y : t -> float -> unit

  val set_z : t -> float -> unit

  val copy' : target:t -> t -> unit

  val copy : t -> t

  val normalize' : target:t -> t -> unit

  val normalize : t -> t

  val reciprocal' : target:t -> t -> unit

  val reciprocal : t -> t

  val round' : target:t -> t -> unit

  val round : t -> t

  val floor' : target:t -> t -> unit

  val floor : t -> t

  val neg' : target:t -> t -> unit

  val neg : t -> t

  val add' : target:t -> t -> t -> unit

  val add : t -> t -> t

  val sub' : target:t -> t -> t -> unit

  val sub : t -> t -> t

  val mul' : target:t -> t -> t -> unit

  val mul : t -> t -> t

  val div' : target:t -> t -> t -> unit

  val div : t -> t -> t

  val cross' : target:t -> t -> t -> unit

  val cross : t -> t -> t

  val mulf' : target:t -> t -> float -> unit

  val mulf : t -> float -> t

  val divf' : target:t -> t -> float -> unit

  val divf : t -> float -> t

  val rotate_2d' : target:t -> t -> float -> unit

  val rotate_2d : t -> float -> t

  val lerp' : target:t -> t -> t -> float -> unit

  val lerp : t -> t -> float -> t

  val move_x : t -> float -> unit

  val move_y : t -> float -> unit

  val move_z : t -> float -> unit

  val of_rotation : float -> t
end

module Obox : sig
  type t

  val make : pos:Vector.t -> pivot:Vector.t -> size:Vector.t -> float -> t

  val copy : t -> t

  val get_center : t -> Vector.t

  val move : t -> Vector.t -> t

  val rotate_2d : t -> float -> t

  val is_inside : t -> Vector.t -> bool

  val is_inside_2d : t -> Vector.t -> bool
end

module Texture : sig
  type t

  val create_from_file : string -> bool -> t option

  val delete : t -> Status.t

  val clear_cache : unit -> Status.t

  val get_size : t -> (float * float) option
end

module Graphic : sig
  type t

  val create : unit -> t option

  val create_from_config : string -> t option

  val delete : t -> Status.t

  val set_size : t -> Vector.t -> Status.t

  val get_size : t -> Vector.t

  val set_origin : t -> Vector.t -> Status.t

  val get_origin : t -> Vector.t

  val set_flip : t -> bool -> bool -> Status.t

  val set_pivot : t -> Vector.t -> Status.t

  val set_data : t -> Structure.t -> Status.t

  val to_structure : t -> Structure.t
end

module Display : sig
  module Rgba : sig end

  module Draw : sig end
end

module Sound_status : sig
  type t
end

module Sound : sig
  type t

  val create_from_config : string -> t option

  val get_name : t -> string

  val get_status : t -> Sound_status.t

  val play : t -> Status.t

  val pause : t -> Status.t

  val stop : t -> Status.t

  val get_duration : t -> float

  val get_pitch : t -> float

  val set_pitch : t -> float -> Status.t

  val get_volume : t -> float

  val set_volume : t -> float -> Status.t

  val get_attenuation : t -> float

  val set_attenuation : t -> float -> Status.t
end

module Resource : sig
  type group = Config

  val pp : group Fmt.t

  val group_of_string : string -> group

  val string_of_group : group -> string

  val add_storage : group -> string -> bool -> Status.t
end

module Mouse_button : sig
  type t
end

module Mouse_axis : sig
  type t
end

module Mouse : sig
  val is_button_pressed : Mouse_button.t -> bool

  val get_position : unit -> Vector.t option

  val get_move_delta : unit -> Vector.t option

  val get_wheel_delta : unit -> float

  val show_cursor : bool -> Status.t

  val set_cursor : string -> Vector.t option -> Status.t

  val get_button_name : Mouse_button.t -> string

  val get_axis_name : Mouse_axis.t -> string
end

module Input_type : sig
  type t
end

module Input_mode : sig
  type t
end

module Input : sig
  val is_active : string -> bool

  val has_new_status : string -> bool

  val has_been_activated : string -> bool

  val get_binding :
    string -> int -> (Input_type.t * int * Input_mode.t) Status.result

  val get_binding_name : Input_type.t -> int -> Input_mode.t -> string
end

module Physics : sig
  val get_gravity : unit -> Vector.t option

  val set_gravity : Vector.t -> Status.t
end

module Object : sig
  type t

  val compare : t -> t -> int

  val equal : t -> t -> bool

  val create_from_config : string -> t option

  val enable : t -> bool -> unit

  val enable_recursive : t -> bool -> unit

  val is_enabled : t -> bool

  val pause : t -> bool -> unit

  val is_paused : t -> bool

  val get_name : t -> string

  val get_child_object : t -> t option

  val get_bounding_box : t -> Obox.t option

  val add_fx : ?delay:float -> unique:bool -> t -> string -> Status.t

  val remove_fx : t -> string -> Status.t

  val get_rotation : t -> float

  val set_rotation : t -> float -> Status.t

  val get_world_position : t -> Vector.t option

  val set_world_position : t -> Vector.t -> Status.t

  val get_position : t -> Vector.t option

  val set_position : t -> Vector.t -> Status.t

  val get_scale : t -> Vector.t option

  val set_scale : t -> Vector.t -> Status.t

  val set_text_string : t -> string -> Status.t

  val get_text_string : t -> string

  val set_life_time : t -> float -> Status.t

  val get_life_time : t -> float

  val get_active_time : t -> float

  val add_time_line_track : t -> string -> Status.t

  val remove_time_line_track : t -> string -> Status.t

  val enable_time_line : t -> bool -> unit

  val is_time_line_enabled : t -> bool

  val apply_force : t -> Vector.t -> Vector.t option -> Status.t

  val apply_impulse : t -> Vector.t -> Vector.t option -> Status.t

  val apply_torque : t -> float -> Status.t

  val set_speed : t -> Vector.t -> Status.t

  val get_speed : t -> Vector.t option

  val set_relative_speed : t -> Vector.t -> Status.t

  val get_relative_speed : t -> Vector.t option

  val set_angular_velocity : t -> float -> Status.t

  val get_angular_velocity : t -> float

  val set_custom_gravity : t -> Vector.t -> Status.t

  val get_custom_gravity : t -> Vector.t option

  val get_mass : t -> float

  val get_mass_center : t -> Vector.t option

  type collision = {
    colliding_object : t;
    contact : Vector.t;
    normal : Vector.t;
  }

  val raycast :
    ?self_flags:int ->
    ?check_mask:int ->
    ?early_exit:bool ->
    v0:Vector.t ->
    v1:Vector.t ->
    collision option

  val set_rgb : t -> Vector.t -> Status.t

  val set_rgb_recursive : t -> Vector.t -> unit

  val set_alpha : t -> float -> Status.t

  val set_alpha_recursive : t -> float -> unit

  val set_target_anim : t -> string -> Status.t

  val add_sound : t -> string -> Status.t

  val remove_sound : t -> string -> Status.t

  val get_last_added_sound : t -> Sound.t option

  val set_volume : t -> float -> Status.t

  val set_pitch : t -> float -> Status.t

  val play : t -> Status.t

  val stop : t -> Status.t

  val link_structure : t -> Structure.t -> Status.t

  val get_neighbor_list : Obox.t -> String_id.t -> t list option

  val get_list : String_id.t -> t list

  val pick : Vector.t -> String_id.t -> t option

  val box_pick : Obox.t -> String_id.t -> t option

  val get_default_group_id : unit -> String_id.t

  val get_group_id : t -> String_id.t

  val set_group_id : t -> String_id.t -> Status.t

  val set_group_id_recursive : t -> String_id.t -> unit

  val to_guid : t -> Structure.guid

  val of_guid : Structure.guid -> t option
end

module Config_event : sig
  type t =
    | Reload_start
    | Reload_stop
end

module Fx_event : sig
  type t =
    | Start
    | Stop
    | Add
    | Remove
    | Loop

  type payload

  val get_name : payload -> string
end

module Input_event : sig
  type t =
    | On
    | Off
    | Select_set

  type payload

  val get_set_name : payload -> string

  val get_input_name : payload -> string
end

module Object_event : sig
  type t =
    | Create
    | Delete
    | Prepare
    | Enable
    | Disable
    | Pause
    | Unpause

  type payload
end

module Physics_event : sig
  type t =
    | Contact_add
    | Contact_remove

  type payload
end

module Sound_event : sig
  type t =
    | Start
    | Stop
    | Add
    | Remove

  type payload

  val get_sound : payload -> Sound.t
end

module Event : sig
  type t

  module Event_type : sig
    type ('event, 'payload) t =
      | Fx : (Fx_event.t, Fx_event.payload) t
      | Input : (Input_event.t, Input_event.payload) t
      | Object : (Object_event.t, Object_event.payload) t
      | Physics : (Physics_event.t, Physics_event.payload) t
      | Sound : (Sound_event.t, Sound_event.payload) t

    type any = Any : (_, _) t -> any
  end

  val get_flag : String_id.t -> String_id.t

  val to_type : t -> Event_type.any

  val to_event : t -> ('event, _) Event_type.t -> 'event

  val get_sender_object : t -> Object.t option

  val get_recipient_object : t -> Object.t option

  val add_handler :
    ('event, 'payload) Event_type.t ->
    (t -> 'event -> 'payload -> Status.t) ->
    Status.t
end

module Module_id : sig
  type t =
    | Clock
    | Main
end

module Clock_type : sig
  type t =
    | Core
    | User
    | Second
end

module Clock_modifier : sig
  type t =
    | Fixed
    | Multiply
    | Maxed
    | None
end

module Clock_priority : sig
  type t =
    | Lowest
    | Lower
    | Low
    | Normal
    | High
    | Higher
    | Highest
end

module Clock : sig
  type t

  module Info : sig
    type clock = t

    type t

    val get_type : t -> Clock_type.t

    val get_tick_size : t -> float

    val get_modifier : t -> Clock_modifier.t

    val get_modifier_value : t -> float

    val get_dt : t -> float

    val get_time : t -> float

    val get_clock : t -> clock option
  end

  val compare : t -> t -> int

  val equal : t -> t -> bool

  val create_from_config : string -> t option

  val create : float -> Clock_type.t -> t option

  val get : string -> t option

  val find_first : float -> Clock_type.t -> t option

  val get_name : t -> string

  val get_info : t -> Info.t

  val set_modifier : t -> Clock_modifier.t -> float -> Status.t

  val set_tick_size : t -> float -> Status.t

  val restart : t -> Status.t

  val pause : t -> Status.t

  val unpause : t -> Status.t

  val is_paused : t -> bool

  val register :
    t -> (Info.t -> unit) -> Module_id.t -> Clock_priority.t -> Status.t
end

module Camera : sig
  type t

  type parent =
    | Camera of t
    | Object of Object.t

  val create_from_config : string -> t option

  val get : string -> t option

  val get_name : t -> string

  val set_parent : t -> parent -> Status.t

  val get_position : t -> Vector.t

  val set_position : t -> Vector.t -> Status.t

  val get_rotation : t -> float

  val set_rotation : t -> float -> Status.t

  val get_zoom : t -> float

  val set_zoom : t -> float -> Status.t

  val set_frustum : t -> float -> float -> float -> float -> Status.t
end

module Viewport : sig
  type t

  val create_from_config : string -> t option

  val get_camera : t -> Camera.t option
end

module Render : sig
  val get_world_position : Vector.t -> Viewport.t -> Vector.t option
end

module Config : sig
  val set_basename : string -> Status.t

  val load : string -> Status.t

  val load_from_memory : string -> int -> Status.t

  val set_bootstrap : (unit -> Status.t) -> Status.t

  val push_section : string -> Status.t

  val pop_section : unit -> Status.t

  val get_current_section : unit -> string

  val select_section : string -> Status.t

  val get_section_count : unit -> int

  val get_section : int -> string

  val get_key_count : unit -> int

  val get_key : int -> string

  val get_parent : string -> string option

  val has_section : string -> bool

  val has_value : string -> bool

  val clear_section : string -> Status.t

  val clear_value : string -> Status.t

  val get_string : string -> string

  val set_string : string -> string -> Status.t

  val get_bool : string -> bool

  val set_bool : string -> bool -> Status.t

  val get_float : string -> float

  val set_float : string -> float -> Status.t

  val get_int : string -> int

  val set_int : string -> int -> Status.t

  val get_vector : string -> Vector.t option

  val set_vector : string -> Vector.t -> Status.t

  val get_list_vector : string -> int option -> Vector.t option

  val set_list_string : string -> string list -> Status.t

  val append_list_string : string -> string list -> Status.t

  val get : (string -> 'a) -> section:string -> key:string -> 'a Status.result

  val get_list_item :
    (string -> int option -> 'a) ->
    int option ->
    section:string ->
    key:string ->
    'a Status.result

  val get_list :
    (string -> int option -> 'a) ->
    section:string ->
    key:string ->
    'a list Status.result

  val is_list : string -> bool

  val get_sections : unit -> string list

  val get_current_section_keys : unit -> string list

  val get_section_keys : string -> string list Status.result
end

module Orx_thread : sig
  val set_ocaml_callbacks : unit -> unit
end

module Main : sig
  val execute :
    init:(unit -> Status.t) ->
    run:(unit -> Status.t) ->
    exit:(unit -> unit) ->
    unit ->
    unit
end

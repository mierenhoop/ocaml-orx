let swap_tuple_list = l => List.map(((a, b)) => (b, a), l);

module Bindings = (F: Ctypes.TYPE) => {
  type structure('a) = F.typ(Ctypes.structure('a));

  // Type alias for orxENUM
  let orx_enum = F.uint;

  module Status = {
    let success = F.constant("orxSTATUS_SUCCESS", F.int);
    let failure = F.constant("orxSTATUS_FAILURE", F.int);
  };

  module Bank = {
    type t;

    // Unsealed structure because the type is anonymous
    let t: structure(t) = F.structure("__orxBANK_t");
  };

  module String_id = {
    type t = Unsigned.UInt32.t;

    let undefined = F.constant("orxSTRINGID_UNDEFINED", F.uint32_t);
  };

  module Rgba = {
    type t;

    let t: structure(t) = F.structure("__orxRGBA_t");
    let rgba = F.field(t, "u32RGBA", F.uint32_t);
    let () = F.seal(t);
  };

  module Vector = {
    type t;

    let t: structure(t) = F.structure("__orxVECTOR_t");
    let x = F.field(t, "fX", F.float);
    let y = F.field(t, "fY", F.float);
    let z = F.field(t, "fZ", F.float);
    let () = F.seal(t);
  };

  module Color = {
    type t;

    let t: structure(t) = F.structure("__orxCOLOR_t");
    let rgb = F.field(t, "vRGB", Vector.t);
    let alpha = F.field(t, "fAlpha", F.float);
    let () = F.seal(t);
  };

  module Handle = {
    let t = F.ptr(F.void);
  };

  module Module_id = {
    type t =
      | Clock
      | Main;

    let clock = F.constant("orxMODULE_ID_CLOCK", F.int64_t);
    let main = F.constant("orxMODULE_ID_MAIN", F.int64_t);

    let map_to_constant = [(Clock, clock), (Main, main)];

    let t =
      F.enum("__orxMODULE_ID_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported module id enum: %Ld", i)
      );
  };

  module Clock_modifier = {
    type t =
      | Fixed
      | Multiply
      | Maxed
      | None;

    let fixed = F.constant("orxCLOCK_MOD_TYPE_FIXED", F.int64_t);
    let multiply = F.constant("orxCLOCK_MOD_TYPE_MULTIPLY", F.int64_t);
    let maxed = F.constant("orxCLOCK_MOD_TYPE_MAXED", F.int64_t);
    let none = F.constant("orxCLOCK_MOD_TYPE_NONE", F.int64_t);

    let map_to_constant = [
      (Fixed, fixed),
      (Multiply, multiply),
      (Maxed, maxed),
      (None, none),
    ];

    let t =
      F.enum("__orxCLOCK_MOD_TYPE_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported clock mod type enum: %Ld", i)
      );
  };

  module Clock_type = {
    type t =
      | Core
      | User
      | Second;

    let core = F.constant("orxCLOCK_TYPE_CORE", F.int64_t);
    let user = F.constant("orxCLOCK_TYPE_USER", F.int64_t);
    let second = F.constant("orxCLOCK_TYPE_SECOND", F.int64_t);

    let map_to_constant = [(Core, core), (User, user), (Second, second)];

    let t =
      F.enum("__orxCLOCK_TYPE_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported clock mod type enum: %Ld", i)
      );
  };

  module Clock_info = {
    type t;

    let t: structure(t) = F.structure("__orxCLOCK_INFO_t");
    let clock_type = F.field(t, "eType", Clock_type.t);
    let tick_size = F.field(t, "fTickSize", F.float);
    let modifier = F.field(t, "eModType", Clock_modifier.t);
    let modifier_value = F.field(t, "fModValue", F.float);
    let dt = F.field(t, "fDT", F.float);
    let time = F.field(t, "fTime", F.float);
    let () = F.seal(t);
  };

  module Clock_priority = {
    type t =
      | Lowest
      | Lower
      | Low
      | Normal
      | High
      | Higher
      | Highest;

    let lowest = F.constant("orxCLOCK_PRIORITY_LOWEST", F.int64_t);
    let lower = F.constant("orxCLOCK_PRIORITY_LOWER", F.int64_t);
    let low = F.constant("orxCLOCK_PRIORITY_LOW", F.int64_t);
    let normal = F.constant("orxCLOCK_PRIORITY_NORMAL", F.int64_t);
    let high = F.constant("orxCLOCK_PRIORITY_HIGH", F.int64_t);
    let higher = F.constant("orxCLOCK_PRIORITY_HIGHER", F.int64_t);
    let highest = F.constant("orxCLOCK_PRIORITY_HIGHEST", F.int64_t);

    let map_to_constant = [
      (Lowest, lowest),
      (Lower, lower),
      (Low, low),
      (Normal, normal),
      (High, high),
      (Higher, higher),
      (Highest, highest),
    ];

    let t =
      F.enum("__orxCLOCK_PRIORITY_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported clock priority enum: %Ld", i)
      );
  };

  module Clock = {
    type t;

    // Unsealed structure because the type is anonymous
    let t: structure(t) = F.structure("__orxCLOCK_t");
  };

  module Fx = {
    type t;

    // Unsealed structure because the type is anonymous
    let t: structure(t) = F.structure("__orxFX_t");
  };

  module Graphic = {
    type t;

    // Unsealed structure because the type is anonymous
    let t: structure(t) = F.structure("__orxGRAPHIC_t");
  };

  module Sound = {
    type t;

    // Unsealed structure because the type is anonymous
    let t: structure(t) = F.structure("__orxSOUND_t");
  };

  module Sound_status = {
    type t =
      | Play
      | Pause
      | Stop
      | None;

    let play = F.constant("orxSOUND_STATUS_PLAY", F.int64_t);
    let pause = F.constant("orxSOUND_STATUS_PAUSE", F.int64_t);
    let stop = F.constant("orxSOUND_STATUS_STOP", F.int64_t);
    let none = F.constant("orxSOUND_STATUS_NONE", F.int64_t);

    let map_to_constant = [
      (Play, play),
      (Pause, pause),
      (Stop, stop),
      (None, none),
    ];

    let t =
      F.enum("__orxSOUND_STATUS_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported sound status enum: %Ld", i)
      );
  };

  module Mouse_button = {
    type t =
      | Left
      | Right
      | Middle
      | Extra_1
      | Extra_2
      | Extra_3
      | Extra_4
      | Extra_5
      | Wheel_up
      | Wheel_down;

    let make = name => F.constant("orxMOUSE_BUTTON_" ++ name, F.int64_t);

    let left = make("LEFT");
    let right = make("RIGHT");
    let middle = make("MIDDLE");
    let extra_1 = make("EXTRA_1");
    let extra_2 = make("EXTRA_2");
    let extra_3 = make("EXTRA_3");
    let extra_4 = make("EXTRA_4");
    let extra_5 = make("EXTRA_5");
    let wheel_up = make("WHEEL_UP");
    let wheel_down = make("WHEEL_DOWN");

    let map_to_constant = [
      (Left, left),
      (Right, right),
      (Middle, middle),
      (Extra_1, extra_1),
      (Extra_2, extra_2),
      (Extra_3, extra_3),
      (Extra_4, extra_4),
      (Extra_5, extra_5),
      (Wheel_up, wheel_up),
      (Wheel_down, wheel_down),
    ];

    let t =
      F.enum("__orxMOUSE_BUTTON_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported mouse button enum: %Ld", i)
      );
  };

  module Mouse_axis = {
    type t =
      | X
      | Y;

    let make = name => F.constant("orxMOUSE_AXIS_" ++ name, F.int64_t);

    let x = make("X");
    let y = make("Y");

    let map_to_constant = [(X, x), (Y, y)];

    let t =
      F.enum("__orxMOUSE_AXIS_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported mouse axis enum: %Ld", i)
      );
  };

  module Structure = {
    type t;

    // Unsealed structure until we expose its form in these bindings
    let t: structure(t) = F.structure("__orxSTRUCTURE_t");
  };

  module Input_type = {
    type t =
      | Keyboard_key
      | Mouse_button
      | Mouse_axis
      | Joystick_button
      | Joystick_axis
      | External
      | None;

    let keyboard_key = F.constant("orxINPUT_TYPE_KEYBOARD_KEY", F.int64_t);
    let mouse_button = F.constant("orxINPUT_TYPE_MOUSE_BUTTON", F.int64_t);
    let mouse_axis = F.constant("orxINPUT_TYPE_MOUSE_AXIS", F.int64_t);
    let joystick_button =
      F.constant("orxINPUT_TYPE_JOYSTICK_BUTTON", F.int64_t);
    let joystick_axis = F.constant("orxINPUT_TYPE_JOYSTICK_AXIS", F.int64_t);
    let external_ = F.constant("orxINPUT_TYPE_EXTERNAL", F.int64_t);
    let none = F.constant("orxINPUT_TYPE_NONE", F.int64_t);

    let map_to_constant = [
      (Keyboard_key, keyboard_key),
      (Mouse_button, mouse_button),
      (Mouse_axis, mouse_axis),
      (Joystick_button, joystick_button),
      (Joystick_axis, joystick_axis),
      (External, external_),
      (None, none),
    ];

    let t =
      F.enum("__orxINPUT_TYPE_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported input type enum: %Ld", i)
      );
  };

  module Input_mode = {
    type t =
      | Full
      | Positive
      | Negative;

    let full = F.constant("orxINPUT_MODE_FULL", F.int64_t);
    let positive = F.constant("orxINPUT_MODE_POSITIVE", F.int64_t);
    let negative = F.constant("orxINPUT_MODE_NEGATIVE", F.int64_t);

    let map_to_constant = [
      (Full, full),
      (Positive, positive),
      (Negative, negative),
    ];

    let t =
      F.enum("__orxINPUT_MODE_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported input mode enum: %Ld", i)
      );
  };

  module Event_type = {
    type t =
      | Anim
      | Clock
      | Config
      | Display
      | Fx
      | Input
      | Locale
      | Object
      | Render
      | Physics
      | Resource
      | Shader
      | Sound
      | Spawner
      | System
      | Texture
      | Timeline
      | Viewport;

    let anim = F.constant("orxEVENT_TYPE_ANIM", F.int64_t);
    let clock = F.constant("orxEVENT_TYPE_CLOCK", F.int64_t);
    let config = F.constant("orxEVENT_TYPE_CONFIG", F.int64_t);
    let display = F.constant("orxEVENT_TYPE_DISPLAY", F.int64_t);
    let fx = F.constant("orxEVENT_TYPE_FX", F.int64_t);
    let input = F.constant("orxEVENT_TYPE_INPUT", F.int64_t);
    let locale = F.constant("orxEVENT_TYPE_LOCALE", F.int64_t);
    let object_ = F.constant("orxEVENT_TYPE_OBJECT", F.int64_t);
    let render = F.constant("orxEVENT_TYPE_RENDER", F.int64_t);
    let physics = F.constant("orxEVENT_TYPE_PHYSICS", F.int64_t);
    let resource = F.constant("orxEVENT_TYPE_RESOURCE", F.int64_t);
    let shader = F.constant("orxEVENT_TYPE_SHADER", F.int64_t);
    let sound = F.constant("orxEVENT_TYPE_SOUND", F.int64_t);
    let spawner = F.constant("orxEVENT_TYPE_SPAWNER", F.int64_t);
    let system = F.constant("orxEVENT_TYPE_SYSTEM", F.int64_t);
    let texture = F.constant("orxEVENT_TYPE_TEXTURE", F.int64_t);
    let timeline = F.constant("orxEVENT_TYPE_TIMELINE", F.int64_t);
    let viewport = F.constant("orxEVENT_TYPE_VIEWPORT", F.int64_t);

    let map_to_constant = [
      (Anim, anim),
      (Clock, clock),
      (Config, config),
      (Display, display),
      (Fx, fx),
      (Input, input),
      (Locale, locale),
      (Object, object_),
      (Render, render),
      (Physics, physics),
      (Resource, resource),
      (Shader, shader),
      (Sound, sound),
      (Spawner, spawner),
      (System, system),
      (Texture, texture),
      (Timeline, timeline),
      (Viewport, viewport),
    ];

    let map_from_constant = swap_tuple_list(map_to_constant);

    let t =
      F.enum("__orxEVENT_TYPE_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported event type enum: %Ld", i)
      );
  };

  module Config_event = {
    type t =
      | Reload_start
      | Reload_stop;

    let make = tag => F.constant("orxCONFIG_EVENT_" ++ tag, F.int64_t);
    let reload_start = make("RELOAD_START");
    let reload_stop = make("RELOAD_STOP");

    let map_to_constant = [
      (Reload_start, reload_start),
      (Reload_stop, reload_stop),
    ];

    let map_from_constant = swap_tuple_list(map_to_constant);

    let t =
      F.enum("__orxCONFIG_EVENT_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported config event type enum: %Ld", i)
      );
  };

  module Fx_event = {
    type t =
      | Start
      | Stop
      | Add
      | Remove
      | Loop;

    let start = F.constant("orxFX_EVENT_START", F.int64_t);
    let stop = F.constant("orxFX_EVENT_STOP", F.int64_t);
    let add = F.constant("orxFX_EVENT_ADD", F.int64_t);
    let remove = F.constant("orxFX_EVENT_REMOVE", F.int64_t);
    let loop = F.constant("orxFX_EVENT_LOOP", F.int64_t);

    let map_to_constant = [
      (Start, start),
      (Stop, stop),
      (Add, add),
      (Remove, remove),
      (Loop, loop),
    ];

    let map_from_constant = swap_tuple_list(map_to_constant);

    let t =
      F.enum("__orxFX_EVENT_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported fx event type enum: %Ld", i)
      );

    module Payload = {
      type t;

      let t: structure(t) = F.structure("__orxFX_EVENT_PAYLOAD_t");
      let fx = F.field(t, "pstFX", F.ptr(Fx.t));
      let name = F.field(t, "zFXName", F.string);
      let () = F.seal(t);
    };
  };

  module Input_event = {
    type t =
      | On
      | Off
      | Select_set;

    let on = F.constant("orxINPUT_EVENT_ON", F.int64_t);
    let off = F.constant("orxINPUT_EVENT_OFF", F.int64_t);
    let select_set = F.constant("orxINPUT_EVENT_SELECT_SET", F.int64_t);

    let map_to_constant = [(On, on), (Off, off), (Select_set, select_set)];

    let map_from_constant = swap_tuple_list(map_to_constant);

    let t =
      F.enum("__orxINPUT_EVENT_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported input event type enum: %Ld", i)
      );

    module Payload = {
      type t;

      // orxINPUT_KU32_BINDING_NUMBER = 8 in orxInput.h
      let binding_number = 8;

      let t: structure(t) = F.structure("__orxINPUT_EVENT_PAYLOAD_t");
      let set_name = F.field(t, "zSetName", F.string);
      let input_name = F.field(t, "zInputName", F.string);
      let input_type =
        F.field(t, "aeType", F.array(binding_number, Input_type.t));
      let id = F.field(t, "aeID", F.array(binding_number, orx_enum));
      let mode = F.field(t, "aeMode", F.array(binding_number, Input_mode.t));
      let value = F.field(t, "afValue", F.array(binding_number, F.float));
      let () = F.seal(t);
    };
  };

  module Physics_event = {
    type t =
      | Contact_add
      | Contact_remove;

    let contact_add = F.constant("orxPHYSICS_EVENT_CONTACT_ADD", F.int64_t);
    let contact_remove =
      F.constant("orxPHYSICS_EVENT_CONTACT_REMOVE", F.int64_t);

    let map_to_constant = [
      (Contact_add, contact_add),
      (Contact_remove, contact_remove),
    ];

    let map_from_constant = swap_tuple_list(map_to_constant);

    let t =
      F.enum("__orxPHYSICS_EVENT_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported physics event type enum: %Ld", i)
      );

    module Payload = {
      type t;

      let t: structure(t) = F.structure("__orxPHYSICS_EVENT_PAYLOAD_t");
      let position = F.field(t, "vPosition", Vector.t);
      let normal = F.field(t, "vNormal", Vector.t);
      let sender_part_name = F.field(t, "zSenderPartName", F.string);
      let recipient_part_name = F.field(t, "zRecipientPartName", F.string);
      let () = F.seal(t);
    };
  };

  module Sound_event = {
    type t =
      | Start
      | Stop
      | Add
      | Remove;
    /* TODO: If someone finds a way to safely handle these from OCaml, add
       support back in.
       | Packet
       | Recording_start
       | Recording_stop
       | Recording_packet
       | None; */

    let make = tag => F.constant("orxSOUND_EVENT_" ++ tag, F.int64_t);
    let start = make("START");
    let stop = make("STOP");
    let add = make("ADD");
    let remove = make("REMOVE");
    /* let packet = make("PACKET");
       let recording_start = make("RECORDING_START");
       let recording_stop = make("RECORDING_STOP");
       let recording_packet = make("RECORDING_PACKET");
       let none = make("NONE"); */

    let map_to_constant = [
      (Start, start),
      (Stop, stop),
      (Add, add),
      (Remove, remove),
      /* (Packet, packet),
         (Recording_start, recording_start),
         (Recording_stop, recording_stop),
         (Recording_packet, recording_packet),
         (None, none), */
    ];

    let map_from_constant = swap_tuple_list(map_to_constant);

    let t =
      F.enum("__orxSOUND_EVENT_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported sound event type enum: %Ld", i)
      );

    module Payload = {
      type t;

      let t: structure(t) = F.structure("__orxSOUND_EVENT_PAYLOAD_t");
      let sound = F.field(t, "pstSound", F.ptr(Sound.t));
      let () = F.seal(t);
    };
  };

  module Texture_event = {
    type t =
      | Create
      | Delete
      | Load;

    let create = F.constant("orxTEXTURE_EVENT_CREATE", F.int64_t);
    let delete = F.constant("orxTEXTURE_EVENT_DELETE", F.int64_t);
    let load = F.constant("orxTEXTURE_EVENT_LOAD", F.int64_t);

    let map_to_constant = [
      (Create, create),
      (Delete, delete),
      (Load, load),
    ];

    let map_from_constant = swap_tuple_list(map_to_constant);

    let t =
      F.enum("__orxTEXTURE_EVENT_t", map_to_constant, ~unexpected=i =>
        Fmt.invalid_arg("unsupported texture event type enum: %Ld", i)
      );
  };

  module Event = {
    type t;

    let t: structure(t) = F.structure("__orxEVENT_t");
    let event_type = F.field(t, "eType", Event_type.t);
    let event_id = F.field(t, "eID", orx_enum);
    let sender = F.field(t, "hSender", Handle.t);
    let recipient = F.field(t, "hRecipient", Handle.t);
    let payload = F.field(t, "pstPayload", F.ptr(F.void));
    let context = F.field(t, "pContext", F.ptr(F.void));
    let () = F.seal(t);
  };

  module Camera = {
    type t;

    // Unsealed structure because the type is anonymous
    let t: structure(t) = F.structure("__orxCAMERA_t");
  };

  module Object = {
    type t;

    // Unsealed structure because the type is anonymous
    let t: structure(t) = F.structure("__orxOBJECT_t");
  };

  module Obox = {
    type t;

    let t: structure(t) = F.structure("__orxOBOX_t");
    let field = F.field(t);
    let position = field("vPosition", Vector.t);
    let pivot = field("vPivot", Vector.t);
    let x = field("vX", Vector.t);
    let y = field("vY", Vector.t);
    let z = field("vZ", Vector.t);
    let () = F.seal(t);
  };

  module Texture = {
    type t;

    // Unsealed structure because the type is anonymous
    let t: structure(t) = F.structure("__orxTEXTURE_t");
  };

  module Viewport = {
    type t;

    // Unsealed structure because the type is anonymous
    let t: structure(t) = F.structure("__orxVIEWPORT_t");
  };
};
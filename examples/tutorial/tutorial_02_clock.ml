(* Adaptation of the clock tutorial from Orx *)
(* This example is a direct adaptation of the 02_Clock.c tutorial from Orx *)

(* Helper functions for unwrapping values. *)
let get_ok (r : ('a, _) result) : 'a =
  match r with
  | Ok x -> x
  | Error _ -> invalid_arg "get_ok: argument must be Ok(_)"
let get_some (o : 'a option) : 'a =
  match o with
  | Some x -> x
  | None -> invalid_arg "get_some: argument must be Some(_)"

module State = struct
  module Clock_map = Map.Make (Orx.Clock)

  type t = Orx.Object.t Clock_map.t ref

  let state : t = ref Clock_map.empty

  let get () = !state

  let add (clock : Orx.Clock.t) (o : Orx.Object.t) : unit =
    state := Clock_map.add clock o !state
end

let update (clock_info : Orx.Clock.Info.t) =
  Orx.Config.push_section "Main" |> get_ok;

  if Orx.Config.get_bool "DisplayLog" then
    Fmt.pr "<%s>: Time = %.3f / DT = %.3f@."
      (Orx.Clock.get_name (Orx.Clock.Info.get_clock clock_info |> get_some))
      (Orx.Clock.Info.get_time clock_info)
      (Orx.Clock.Info.get_dt clock_info);

  Orx.Config.pop_section () |> get_ok;

  let clock = Orx.Clock.Info.get_clock clock_info |> get_some in
  let obj = State.Clock_map.find clock (State.get ()) in
  Orx.Object.set_rotation obj (Float.pi *. Orx.Clock.Info.get_time clock_info)
  |> get_ok

let input_update (_clock_info : Orx.Clock.Info.t) =
  Orx.Config.push_section "Main" |> get_ok;
  if Orx.Input.has_been_activated "Log" then
    Orx.Config.set_bool "DisplayLog" (not (Orx.Config.get_bool "DisplayLog"))
    |> get_ok;
  Orx.Config.pop_section () |> get_ok;

  match Orx.Clock.get "Clock1" with
  | None -> ()
  | Some clock ->
    if Orx.Input.is_active "Faster" then
      Orx.Clock.set_modifier clock Multiply 4.0 |> get_ok
    else if Orx.Input.is_active "Slower" then
      Orx.Clock.set_modifier clock Multiply 0.25 |> get_ok
    else if Orx.Input.is_active "Normal" then
      Orx.Clock.set_modifier clock None 0.0 |> get_ok

let init () =
  let get_name (binding : string) : string =
    let (type_, id, mode) = Orx.Input.get_binding binding 0 |> get_ok in
    Orx.Input.get_binding_name type_ id mode
  in
  Fmt.pr
    ("- Press '%s' to toggle log display@."
    ^^ "- To stretch time for the first clock (updating the box):@."
    ^^ " . Press numpad '%s' to set it 4 times faster@."
    ^^ " . Press numpad '%s' to set it 4 times slower@."
    ^^ " . Press numpad '%s' to set it back to normal@."
    )
    (get_name "Log") (get_name "Faster") (get_name "Slower") (get_name "Normal");

  Orx.Viewport.create_from_config "Viewport" |> get_some |> ignore;

  let object1 = Orx.Object.create_from_config "Object1" |> get_some in
  let object2 = Orx.Object.create_from_config "Object2" |> get_some in

  let clock1 = Orx.Clock.create_from_config "Clock1" |> get_some in
  let clock2 = Orx.Clock.create_from_config "Clock2" |> get_some in

  State.add clock1 object1;
  State.add clock2 object2;

  Orx.Clock.register clock1 update Main Normal |> get_ok;
  Orx.Clock.register clock2 update Main Normal |> get_ok;

  let main_clock = Orx.Clock.find_first (-1.0) Core |> get_some in
  Orx.Clock.register main_clock input_update Main Normal |> get_ok;

  Ok ()

let run () =
  if Orx.Input.is_active "Quit" then
    Error ()
  else
    Ok ()

let exit () = ()

let bootstrap () =
  (* Tell Orx where to look for our configuration file(s) *)
  Orx.Resource.add_storage Orx.Resource.Config "examples/tutorial/data" false

let () =
  Orx.Config.set_bootstrap bootstrap |> get_ok;
  Orx.Config.set_basename "02_Clock" |> get_ok;
  Orx.Main.execute ~init ~run ~exit ()
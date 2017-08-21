type done_;


/** abstract type which ensure middleware function must either
    call the [next] function or one of the [send] function on the
    response object.

    This should be a great argument for OCaml, the type system
    prevents silly error which in this case would make the server hang */

/** TODO : maybe this should be a more common module like bs-error */
module Error = {
  type t;

  /** Error type */
  external message : t => option string =
    "" [@@bs.send] [@@bs.return null_undefined_to_opt];
  external name : t => option string =
    "" [@@bs.send] [@@bs.return null_undefined_to_opt];
};

module Request = {
  type t;
  external get : t => string => string = "get" [@@bs.send];
};

module Context = {
  type t = Js.t {. request : Request.t};
  let get ctx key => Request.get ctx##request key;
};

type next = unit => Js.Promise.t unit;

type middleware = Context.t => next => Js.Promise.t unit;

module App = {
  type t;
  external make : unit => t = "koa" [@@bs.module] [@@bs.new];
  external listen :
    t =>
    port::int? =>
    hostname::string? =>
    backlog::int? =>
    callback::(Js.Null_undefined.t Js.Exn.t => unit)? =>
    unit =
    "listen" [@@bs.send];
  external use : t => middleware => unit = "use" [@@bs.send];
};

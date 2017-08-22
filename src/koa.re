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
  external message : t => option string = "" [@@bs.send] [@@bs.return null_undefined_to_opt];
  external name : t => option string = "" [@@bs.send] [@@bs.return null_undefined_to_opt];
};

module Request = {
  type t;
  external get : t => string => option string = "get" [@@bs.send];
  external header : t => Js.Dict.t string = "header" [@@bs.get];
  external set_header : t => Js.Dict.t string => unit = "header" [@@bs.set];
  external raw_method : t => string = "method" [@@bs.get];
  type method_ =
    | Get
    | Post
    | Put
    | Delete
    | Head
    | Options
    | Trace
    | Connect;
  let method: t => method_ =
    fun req =>
      switch (raw_method req) {
      | "GET" => Get
      | "POST" => Post
      | "PUT" => Put
      | "DELETE" => Delete
      | "HEAD" => Head
      | "OPTIONS" => Options
      | "TRACE" => Trace
      | "CONNECT" => Connect
      | s => failwith ("Koa.Request.method_ Unexpected method: " ^ s)
      };
  external set_method : t => method_ => unit = "method" [@@bs.set];
  external length : t => int = "length" [@@bs.get];
  external url : t => string = "url" [@@bs.get];
  external set_url : t => string => unit = "url" [@@bs.set];
  external original_url : t => string = "originalUrl" [@@bs.get];
  external set_original_url : t => string => unit = "originalUrl" [@@bs.set];
  external origin : t => string = "origin" [@@bs.get];
  external set_origin : t => string => unit = "origin" [@@bs.set];
  external href : t => string = "href" [@@bs.get];
  external set_href : t => string => unit = "href" [@@bs.set];
  external path : t => string = "path" [@@bs.get];
  external set_path : t => string => unit = "path" [@@bs.set];
  external querystring : t => string = "querystring" [@@bs.get];
  external set_querystring : t => string => unit = "querystring" [@@bs.set];
  external search : t => string = "search" [@@bs.get];
  external set_search : t => string => unit = "search" [@@bs.set];
  external host : t => string = "host" [@@bs.get];
  external set_host : t => string => unit = "host" [@@bs.set];
  external hostname : t => string = "hostname" [@@bs.get];
  external set_hostname : t => string => unit = "hostname" [@@bs.set];
  external type_ : t => string = "type" [@@bs.get];
  external set_type : t => string => unit = "type" [@@bs.set];
  external charset : t => string = "charset" [@@bs.get];
  external set_charset : t => string => unit = "charset" [@@bs.set];
  external set_ : t => string => unit = "" [@@bs.set];
  external fresh : t => bool = "fresh" [@@bs.get];
  external set_fresh : t => bool => unit = "fresh" [@@bs.set];
  external stale : t => bool = "stale" [@@bs.get];
  external set_stale : t => bool => unit = "stale" [@@bs.set];
  external protocol : t => string = "protocol" [@@bs.get];
  external set_protocol : t => string => unit = "protocol" [@@bs.set];
  external secure : t => bool = "secure" [@@bs.get];
  external set_secure : t => bool => unit = "secure" [@@bs.set];
  external ip : t => string = "ip" [@@bs.get];
  external set_ip : t => string => unit = "ip" [@@bs.set];
  external ips : t => array string = "ips" [@@bs.get];
  external set_ips : t => array string => unit = "ips" [@@bs.set];
  external query : t => Js.Dict.t Js.Json.t = "query" [@@bs.get];
  external set_query : t => Js.Dict.t Js.Json.t => unit = "query" [@@bs.set];
  external subdomains : t => array string = "subdomains" [@@bs.get];
  external is : t => string => bool = "is" [@@bs.send];
  let accepts: array string => t => option string =
    fun types req => {
      module Raw = {
        external accepts : t => array string => Js.Json.t = "accepts" [@@bs.send];
      };
      let ret = Raw.accepts req types;
      let x = Js.Json.classify ret;
      switch x {
      | Js.Json.JSONString x => Some x
      | _ => None
      }
    };
  let acceptsEncodings: array string => t => option string =
    fun types req => {
      module Raw = {
        external acceptsEncodings : t => array string => Js.Json.t =
          "acceptsEncodings" [@@bs.send];
      };
      let ret = Raw.acceptsEncodings req types;
      let x = Js.Json.classify ret;
      switch x {
      | Js.Json.JSONString x => Some x
      | _ => None
      }
    };
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

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
  external get : t => string => option string = "get" [@@bs.send] [@@bs.return nullable];
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
  external raw_accepts : t => array string => Js.Json.t = "accepts" [@@bs.send];
  external raw_accepts_encodings : t => array string => Js.Json.t = "acceptsEncodings" [@@bs.send];
  external raw_accepts_charsets : t => array string => Js.Json.t = "acceptsCharsets" [@@bs.send];
  external raw_accepts_languages : t => array string => Js.Json.t = "acceptsLanguages" [@@bs.send];
  let base_accept ret => {
    let x = Js.Json.classify ret;
    switch x {
    | Js.Json.JSONString x => Some x
    | _ => None
    }
  };
  let accepts types req => base_accept (raw_accepts req types);
  let accepts_encodings types req => base_accept (raw_accepts_encodings req types);
  let accepts_charsets types req => base_accept (raw_accepts_charsets req types);
  let accepts_languages types req => base_accept (raw_accepts_languages req types);
};

module Response = {
  type t;
  external get : t => string => option string = "get" [@@bs.send];
  external set : t => string => string => unit = "set" [@@bs.send];
  external append : t => string => string => unit = "append" [@@bs.send];
  external remove : t => string => unit = "remove" [@@bs.send];
  external header : t => Js.Dict.t string = "header" [@@bs.get];
  external set_header : t => Js.Dict.t string => unit = "header" [@@bs.set];
  external status : t => int = "status" [@@bs.get];
  external set_status : t => int => unit = "status" [@@bs.set];
  external message : t => string = "message" [@@bs.get];
  external set_message : t => string => unit = "message" [@@bs.set];
  external length : t => int = "length" [@@bs.get];
  external set_length : t => int => unit = "length" [@@bs.set];
  external body : t => Js.t 'a = "body" [@@bs.get];
  external set_body : t => Js.t 'a => unit = "length" [@@bs.set];
  external type_ : t => string = "type" [@@bs.get];
  external set_type : t => string => unit = "type" [@@bs.set];
  external is : t => string => bool = "is" [@@bs.send];
  external redirect : t => string => alt::string? => unit = "redirect" [@@bs.send];
  external attachment : t => file::string? => unit = "attachment" [@@bs.send];
  external header_sent : t => bool = "headerSent" [@@bs.send];
  external last_modified : t => option Js.Date.t =
    "lastModified" [@@bs.get] [@@bs.return nullable];
  external set_last_modified : t => Js.Date.t => unit = "lastModified" [@@bs.set];
  external etag : t => string = "etag" [@@bs.get];
  external set_etag : t => string => unit = "etag" [@@bs.set];
  external vary : t => string => bool = "vary" [@@bs.send];
  external flush_headers : t => unit = "flushHeaders" [@@bs.send];
};

module Context = {
  type t = Js.t {. request : Request.t, response : Response.t};
  /* request alias */
  let header ctx => Request.header ctx##request;
  let method ctx => Request.method ctx##request;
  let set_method ctx => Request.set_method ctx##request;
  let url ctx => Request.url ctx##request;
  let set_url ctx => Request.set_url ctx##request;
  let original_url ctx => Request.original_url ctx##request;
  let origin ctx => Request.origin ctx##request;
  let href ctx => Request.href ctx##request;
  let path ctx => Request.path ctx##request;
  let set_path ctx => Request.set_path ctx##request;
  let query ctx => Request.query ctx##request;
  let set_query ctx => Request.set_query ctx##request;
  let querystring ctx => Request.querystring ctx##request;
  let set_querystring ctx => Request.set_querystring ctx##request;
  let host ctx => Request.host ctx##request;
  let hostname ctx => Request.hostname ctx##request;
  let fresh ctx => Request.fresh ctx##request;
  let stale ctx => Request.stale ctx##request;
  let protocol ctx => Request.protocol ctx##request;
  let secure ctx => Request.secure ctx##request;
  let ip ctx => Request.ip ctx##request;
  let ips ctx => Request.ips ctx##request;
  let subdomains ctx => Request.subdomains ctx##request;
  let is ctx => Request.is ctx##request;
  let accepts ctx => Request.accepts ctx##request;
  let accepts_encodings ctx => Request.accepts_encodings ctx##request;
  let accepts_charsets ctx => Request.accepts_charsets ctx##request;
  let accepts_languages ctx => Request.accepts_languages ctx##request;
  let get ctx => Request.get ctx##request;
  /* response alias */
  let body ctx => Response.body ctx##response;
  let set_body ctx => Response.set_body ctx##response;
  let status ctx => Response.status ctx##response;
  let set_status ctx => Response.set_status ctx##response;
  let message ctx => Response.message ctx##response;
  let set_message ctx => Response.set_message ctx##response;
  let set_length ctx => Response.set_length ctx##response;
  let length ctx => Response.length ctx##response;
  let set_type ctx => Response.set_type ctx##response;
  let type_ ctx => Response.type_ ctx##response;
  let header_sent ctx => Response.header_sent ctx##response;
  let redirect ctx => Response.redirect ctx##response;
  let attachment ctx => Response.attachment ctx##response;
  let set ctx => Response.set ctx##response;
  let append ctx => Response.append ctx##response;
  let remove ctx => Response.remove ctx##response;
  let set_last_modified ctx => Response.set_last_modified ctx##response;
  let set_etag ctx => Response.set_etag ctx##response;
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

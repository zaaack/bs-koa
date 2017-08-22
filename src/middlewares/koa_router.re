type config;

module Router = {
  type t;
  external use : list string => Koa.middleware => t = "" [@@bs.send.pipe : t];
  external get : list string => Koa.middleware => t = "" [@@bs.send.pipe : t];
  external post : list string => Koa.middleware => t = "" [@@bs.send.pipe : t];
  external put : list string => Koa.middleware => t = "" [@@bs.send.pipe : t];
  external patch : list string => Koa.middleware => t = "" [@@bs.send.pipe : t];
  external delete : list string => Koa.middleware => t = "" [@@bs.send.pipe : t];
  external del : list string => Koa.middleware => t = "" [@@bs.send.pipe : t];
  external routes : unit => Koa.middleware = "" [@@bs.send];
  external allowed_methods : config::Js.t 'a? => unit => Koa.middleware =
    "allowedMethods" [@@bs.send];
};

external make_config : prefix::string? => unit => config = "" [@@bs.obj];

external make : opts::config? => unit => Router.t = "koa-router" [@@bs.module];

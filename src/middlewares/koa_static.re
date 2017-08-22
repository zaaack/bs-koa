type config;

external make_config :
  maxage::float? => hidden::bool? => index::bool? => unit => config =
  "" [@@bs.obj];

external make : string => opts::config? => Koa.middleware =
  "koa-static" [@@bs.module];

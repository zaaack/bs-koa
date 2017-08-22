external make : string => Koa.middleware => Koa.middleware =
  "koa-mount" [@@bs.module];

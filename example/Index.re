open Koa;

let app = App.make ();

App.use
  app
  (
    fun ctx next => {
      let v = Request.get ctx##request "aa";
      let lastModified = Response.last_modified ctx##response;
      switch lastModified {
      | Some d => Js.log (Js.Date.toLocaleString d)
      | None => Js.log "none"
      };
      Js.log2 "lastModified" lastModified;
      next ()
    }
  );

App.listen
  app
  port::3000
  callback::(
    fun _ => {
      Js.log {j|listen at 3000|j};
      ()
    }
  );

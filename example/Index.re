open Koa;

let app = App.make ();

App.use
  app
  (
    fun ctx next => {
      let v = Request.get ctx##request "aa";
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

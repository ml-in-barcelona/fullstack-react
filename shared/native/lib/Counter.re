[@react.component]
let make = () => {
  let (count, setCount) = React.useState(() => 23);

  let increment = event => {
    let _target = React.Event.Mouse.target(event);
    print_endline("Console works too! " /* ++ target##value */);
    setCount(_ => count + 1);
  };

  <div className={CSS.style([|CSS.color(CSS.whitesmoke)|])}>
    <div
      className={CSS.style([|
        CSS.display(`flex),
        CSS.justifyContent(`left),
        CSS.alignItems(`center),
        CSS.unsafe("gap", "1rem"),
      |])}>
      <p
        className={CSS.style([|
          CSS.margin(`zero),
          CSS.fontSize(`px(25)),
          CSS.fontWeight(`bold),
        |])}>
        {React.string("Counter")}
      </p>
      <button onClick=increment>
        {React.string(Int.to_string(count))}
      </button>
    </div>
    <p className={CSS.style([|CSS.lineHeight(`px(24))|])}>
      {React.string(
         "The HTML (including counter value) comes first from the server"
         ++ " then is updated by React after render or hydration (depending if you are running ReactDOM.render or ReactDOM.hydrate on the client).",
       )}
    </p>
  </div>;
};

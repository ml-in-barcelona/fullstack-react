let useState = initialValue => {
  let (value, setValue) = React.useState(_ => initialValue);
  let setValueStatic = value => setValue(_ => value);
  (value, setValueStatic);
};

module Counter = {
  [@react.component]
  let make = (~name) => {
    let (count, setCount) = useState(2);

    <div>
      <p>
        {React.string(
           name ++ " clicked " ++ Int.to_string(count) ++ " times",
         )}
      </p>
      <button onClick={_ => setCount(count + 1)}>
        {React.string("Click me nooooow!")}
      </button>
    </div>;
  };
};

switch (ReactDOM.querySelector("#root")) {
| Some(el) =>
  let _root = ReactDOM.Client.hydrateRoot(el, <Shared_js.App />);
  ();
| None => ()
};

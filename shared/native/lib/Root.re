[@react.component]
let make = (~children, ~background) => {
  <div
    className={CSS.style([|
      CSS.margin(`zero),
      CSS.padding(`zero),
      CSS.width(`vw(100.)),
      CSS.height(`vh(100.)),
      CSS.backgroundColor(background),
    |])}>
    children
  </div>;
};

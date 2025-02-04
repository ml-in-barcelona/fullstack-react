let unsafeWhenNotZero = (prop, value) =>
  if (value == 0) {
    [||];
  } else {
    [|prop(value |> Theme.px)|];
  };

[@react.component]
let make = (~children=?, ~top=0, ~left=0, ~right=0, ~bottom=0, ~all=0) => {
  let className =
    CSS.style(
      Array.concat([
        unsafeWhenNotZero(CSS.marginTop, top),
        unsafeWhenNotZero(CSS.marginBottom, bottom),
        unsafeWhenNotZero(CSS.marginLeft, left),
        unsafeWhenNotZero(CSS.marginRight, right),
        unsafeWhenNotZero(CSS.margin, all),
      ]),
    );

  <div className>
    {switch (children) {
     | None => React.null
     | Some(c) => c
     }}
  </div>;
};

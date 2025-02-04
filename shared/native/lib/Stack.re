open Theme;

[@react.component]
let make =
    (~gap=0, ~align=`start, ~justify=`around, ~fullHeight=false, ~children) => {
  let className =
    CSS.style([|
      CSS.display(`flex),
      CSS.flexDirection(`column),
      fullHeight ? CSS.height(`percent(100.)) : CSS.height(`auto),
      switch ((align: align)) {
      | `start => CSS.alignItems(`flexStart)
      | `center => CSS.alignItems(`center)
      | `end_ => CSS.alignItems(`flexEnd)
      },
      switch (justify) {
      | `around => CSS.justifyContent(`spaceAround)
      | `between => CSS.justifyContent(`spaceBetween)
      | `evenly => CSS.justifyContent(`spaceEvenly)
      | `start => CSS.justifyContent(`flexStart)
      | `center => CSS.justifyContent(`center)
      | `end_ => CSS.justifyContent(`flexEnd)
      },
      CSS.gap(Theme.px(gap)),
    |]);

  <div className> children </div>;
};

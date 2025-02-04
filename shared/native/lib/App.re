module Hr = {
  [@react.component]
  let make = () => {
    <span
      className={CSS.style([|
        CSS.display(`block),
        CSS.width(`percent(100.)),
        CSS.height(`px(1)),
        CSS.backgroundColor(CSS.gray),
      |])}
    />;
  };
};

module Layout = {
  [@react.component]
  let make = (~children) => {
    <div
      className={CSS.style([|
        CSS.maxWidth(`px(800)),
        CSS.margin2(~v=`zero, ~h=`auto),
        CSS.padding4(
          ~top=`rem(4.0),
          ~bottom=`zero,
          ~left=`rem(2.0),
          ~right=`rem(2.0),
        ),
        Theme.Media.onMobile([|CSS.overflow(`hidden)|]),
      |])}>
      children
    </div>;
  };
};

module Header = {
  type item = {
    label: string,
    link: string,
  };

  module Menu = {
    [@react.component]
    let make = () => {
      let data = [|
        {
          label: "Documentation",
          link: "https://github.com/ml-in-barcelona/server-reason-react",
        },
        {
          label: "Issues",
          link: "https://github.com/ml-in-barcelona/server-reason-react/issues",
        },
        {
          label: "About",
          link: "https://twitter.com/davesnx",
        },
      |];

      <div
        className={CSS.style([|
          CSS.display(`flex),
          CSS.alignItems(`center),
          CSS.justifyContent(`left),
          CSS.unsafe("gap", "1rem"),
        |])}>
        {React.array(
           Belt.Array.mapWithIndex(data, (key, item) =>
             <div
               className={CSS.style([|CSS.display(`block)|])}
               key={Int.to_string(key)}>
               <a
                 href={item.link}
                 target="_blank"
                 className={CSS.style([|
                   CSS.color(CSS.hex("9b9b9b")),
                   CSS.fontSize(`px(14)),
                   CSS.selector(
                     "&:hover",
                     [|CSS.color(Theme.Color.white)|],
                   ),
                 |])}>
                 {React.string(item.label)}
               </a>
             </div>
           ),
         )}
      </div>;
    };
  };

  [@react.component]
  let make = () => {
    <div
      className={CSS.style([|CSS.color(CSS.plum), CSS.fontSize(`px(24))|])}>
      <h1 className={CSS.style([|CSS.margin(`px(0))|])}>
        {React.string("Server Reason React")}
      </h1>
      <Spacer top=2> <Menu /> </Spacer>
    </div>;
  };
};

[@react.component]
let make = () => {
  <Root background=Theme.Color.darkGrey>
    <Layout>
      <Stack gap=8 justify=`start>
        <> <Header /> <Hr /> <Counter /> </>
      </Stack>
    </Layout>
  </Root>;
};

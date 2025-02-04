type verticalAlign = [ | `center];
type horizontalAlign = [
  | `left
  | `center
  | `right
];

[@react.component]
let make = (~h: horizontalAlign=`center, ~v: verticalAlign=`center, ~children) => {
  let className: string = [%cx
    {|
    display: flex;
    flex-direction: column;
    height: 100%;
    width: 100%;
    align-items: $(h);
    justify-content: $(v);
  |}
  ];

  <div className> children </div>;
};

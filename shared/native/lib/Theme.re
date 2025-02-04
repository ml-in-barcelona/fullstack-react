type align = [
  | `start
  | `center
  | `end_
];

type justify = [
  | `around
  | `between
  | `evenly
  | `start
  | `center
  | `end_
];

let unit = v => v * 4;
let px = v => `px(unit(v));

module Media = {
  let maxWidth400 = "(max-width: 400px)";
  let onMobile = rules => {
    CSS.media(maxWidth400, rules);
  };
};

module Color = {
  let white = CSS.white;
  let black = CSS.black;
  let reason = CSS.hex("db4d3f");
  let react = CSS.hex("149eca");
  let lightGrey = CSS.hex("c1c5cd");
  let darkGrey = CSS.hex("292a2d");
  let backgroundBox = CSS.hex("2e3c56");
  let brokenWhite = CSS.hex("eaecee");
  let white01 = CSS.rgba(255, 255, 255, `num(0.1));
};

open Bridge;

module AuthorExcerptsLink = {
  [@react.component]
  let make = (~author) => {
    <Link url={Printf.sprintf("/excerpts/author/%s", author)} txt=author />;
  };
};

[@react.component]
let make = (~authors) => {
  <PageContainer>
    <h1> {React.string("Authors with excerpts")} </h1>
    <ul className="list-disc list-inside">
      {List.mapi(
         (_i, author) =>
           <li key={string_of_int(_i)}> <AuthorExcerptsLink author /> </li>,
         authors,
       )
       |> React.list}
    </ul>
  </PageContainer>;
};

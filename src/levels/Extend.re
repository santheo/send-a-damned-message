type state = {
  prev: option(char),
  direction: option(int),
  result: string,
};

let fn = (x) => {
  List.fold_left(
    (s: state, cur) => {
      switch (s.prev) {
        | Some(prev) => {
          let new_result = Utils.is_alphabet(prev) ? switch (s.direction) {
            | Some(d) => {
              let target = Utils.rotate_alphabet(prev, d);
              cur == target ? s.result : (s.result ++ Char.escaped(target))
            }
            | None => s.result
            } : s.result;
          let new_direction = Utils.is_alphabet(prev) ? Utils.first_true(
            (possible_dir => cur == Utils.rotate_alphabet(prev, possible_dir)),
            [1, 0, -1]
          ) : None;
          let new_result = (s.direction == None && new_direction == None) ? (new_result ++ Char.escaped(prev)) : new_result;
          { direction: new_direction, result: new_result, prev: Some(cur) }
        }
        | None => { direction: s.direction, result: s.result, prev: Some(cur) }
      }
    },
  { result: "", prev: None, direction: None },
  List.concat([Utils.char_list(x), [' ']]),
  ).result;
}

Utils.assert_eq(fn(""), "")
Utils.assert_eq(fn("blah"), "blah")
Utils.assert_eq(fn("bah abz"), "zh cz")
Utils.assert_eq(fn("messsssagess"), "mesages")
Utils.assert_eq(fn("abcdefgh ijklmnop"), "i q")

let level: Types.level = {
  name: "ext",
  fn: fn,
  goal: "a damned message",
  answer: "a daklngfd meqrutage"
}

#let latin = "TeX Gyre Termes"
#let cjk = ("FandolSong", "KaiTi")      // 中文正文与标题（宋体）
#let kai = ("KaiTi", "FandolKai")       // 页眉（楷体）
#let mono = ("Consolas", "FandolSong")  // 代码（含中文注释）

// ---- 正文与标题 ----
#set document(title: [XCPC Templates], author: "Continue")
#set text(font: (latin, ..cjk), size: 10pt, lang: "zh", region: "cn")
#set par(justify: true, leading: 0.4em, first-line-indent: 15pt)

#set heading(numbering: "1.1.1")
#let hsize = (14.4pt, 12pt, 10pt)                    // 1/2/3 级字号
#let hspace = ((8.71pt, 10.59pt), (17.58pt, 15.79pt), (4.58pt, 14.37pt))  // 各级段前/段后
#show heading: it => {
  let lv = calc.clamp(it.level, 1, 3)
  let (above, below) = hspace.at(lv - 1)
  block(above: above, below: below, {
    set text(font: (latin, ..cjk), size: hsize.at(lv - 1), weight: "bold")
    if it.numbering != none {
      numbering(it.numbering, ..counter(heading).at(it.location()))
      h(1em)
    }
    it.body
  })
}

// ---- 代码块 ----
// 行号排在版心左侧的页边距里，代码文字贴版心左边界，边框再外扩 framesep。
#let code-size = 9pt          // 代码字号
#let raw-pitch = 11.49pt      // Typst 排 9pt Consolas 时一行占的高度
#let line-pitch = 13.15pt     // 目标行距，每行下方补 (line-pitch - raw-pitch)
#let numbersep = 9.96pt       // 行号右缘与代码文字的空隙
#let framesep = 3.41pt        // 边框相对代码文字外扩的距离
#let code-inset-y = 6.8pt     // 代码文字距边框的上下留白
#let code-gap = (8pt, 28pt)   // 代码块段前/段后

#set raw(tab-size: 4)
#show raw: set text(font: mono, size: code-size)
#set raw(theme: "theme.tmTheme")
#show raw.where(block: false): set text(1em)     // 行内代码保持正文字号

#let numw-of(n) = measure(text(font: mono, size: code-size, str(n))).width
#let code(path) = {
  let src = read(path)
  let numw = numw-of(src.matches("\n").len() + 1)
  block(
    width: 100%,
    outset: (x: framesep),
    inset: (x: 0pt, y: code-inset-y),
    stroke: 0.4pt,
    above: code-gap.at(0), below: code-gap.at(1),
    breakable: true,
    {
      show raw.line: it => {
        set block(spacing: 0pt, above: 0pt, below: 0pt)  // 否则行间会插进块间距
        pad(bottom: line-pitch - raw-pitch, block(
          inset: (left: -(numw + numbersep)),            // 行号列推到版心左侧
          grid(
            columns: (numw, 1fr),
            column-gutter: numbersep,
            align: (right, left),
            text(size: 1em)[#it.number],
            it.body,
          ),
        ))
      }
      raw(src, lang: "cpp", block: true)
    },
  )
}
#show raw.where(lang: "cpp-ref"): it => code("/" + it.text.trim())

// ---- 说明文件（config.toml 的 description）----
#show math.equation.where(block: true): set block(above: 10pt, below: 10pt)
#let prose(p) = block(above: 0pt, below: 0pt, {
  set par(leading: 0.48em)      // ≈ 每行 18pt，正文的 1.5 倍
  include p
})
#show raw.where(lang: "typ-prose"): it => prose("/" + it.text.trim())

// ---- 页眉页脚：外侧页码、内侧校名 ----
#let head(n) = {
  set text(font: (latin, ..kai), size: 10pt)
  let school = [GuangDong University of Technology]
  let num = [第 #n 页]
  if calc.odd(n) {
    grid(columns: (1fr, auto), align: (left, right), school, num)
  } else {
    grid(columns: (auto, 1fr), align: (left, right), num, school)
  }
  line(length: 100%, stroke: 0.4pt)
}
#set page(paper: "a4", margin: (x: 2cm, y: 2.54cm), footer: none)

// ---- 封面 → 背白页 → 目录（第 1 页）→ 正文 ----
#let today = datetime.today()
#page(numbering: none, header: none)[
  #v(1fr)
  #align(center)[
    #text(size: 25pt, weight: "bold")[XCPC Templates]
    #v(1.6em)
    #line(length: 45%, stroke: 0.8pt)
    #v(1.6em)
    #text(size: 17.3pt)[Skyclad Observer]
    #v(1.2em)
    #text(size: 14.4pt)[Continue]
    #v(0.9em)
    #text(size: 12pt)[#today.display("[month repr:long]") #today.day(), #today.year()]
  ]
  #v(1fr)
]
#page(numbering: none, header: none)[]

#counter(page).update(1)
#set page(numbering: "1", header: context head(counter(page).at(here()).first()))

#show outline.entry: set block(above: 0.57em, below: 0.57em)
#show outline.entry: set outline.entry(fill: repeat([.], gap: 0.35em))
#show outline.entry.where(level: 1): set block(above: 0.57em + 7.4pt)
#show outline.entry.where(level: 1): set text(weight: "bold")
#outline(
  title: [Contents],
  depth: 3,
  indent: depth => if depth == 0 { 0pt } else if depth == 1 { 1.5em } else { 3.8em },
)
#pagebreak()

#include "body.typ"

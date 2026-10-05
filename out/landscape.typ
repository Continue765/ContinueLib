#let latin = "TeX Gyre Termes"
#let cjk = ("FandolSong", "KaiTi")
#let kai = ("KaiTi", "FandolKai")
#let mono = ("Consolas", "FandolSong")

// ---- 正文与紧凑标题 ----
#set document(title: [XCPC Templates], author: "Continue")
#set text(font: (latin, ..cjk), size: 9pt, lang: "zh", region: "cn")
#set par(justify: true, leading: 0.42em, first-line-indent: 0pt)
#set heading(numbering: "1.1.1")
#let hsize = (12pt, 10pt, 9pt)
#let hspace = ((9pt, 7pt), (8pt, 6pt), (7pt, 5pt))
#show heading: it => {
  let lv = calc.clamp(it.level, 1, 3)
  let (above, below) = hspace.at(lv - 1)
  block(above: above, below: below, sticky: true, {
    set text(size: hsize.at(lv - 1), weight: "bold")
    if it.numbering != none {
      numbering(it.numbering, ..counter(heading).at(it.location()))
      h(0.8em)
    }
    if lv == 3 { text(fill: rgb("0000cc"), it.body) } else { it.body }
  })
}

// ---- 代码框：外置行号，续行不重复编号，框可跨栏/跨页 ----
#let code-size = 8pt
#let number-size = 5pt
#let code-line-gap = 1.8pt    // 每个源码行额外留白，续行用 par 的行距
#let framesep = 2.5pt
#let numbersep = 4.5pt
#set raw(tab-size: 4, theme: "landscape.tmTheme")
#show raw: set text(font: mono, size: code-size)
#show raw.where(block: false): set text(1em)

#let visible-code(path) = {
  let lines = read(path).split("\n").filter(line => {
    line.trim().matches(regex("^#\\s*(include\\b|pragma\\s+once\\b)")).len() == 0
  })
  while lines.len() > 0 and lines.first().trim() == "" {
    lines = lines.slice(1)
  }
  while lines.len() > 0 and lines.last().trim() == "" {
    lines = lines.slice(0, -1)
  }
  lines.join("\n")
}
#let code(path) = {
  let src = visible-code(path)
  let numw = measure(text(font: mono, size: number-size,
    str(src.matches("\n").len() + 1))).width
  block(
    width: 100%,
    outset: (x: framesep),
    inset: (x: 0pt, y: 4pt),
    stroke: 0.35pt,
    above: 5pt, below: 8pt,
    breakable: true,
    {
      show raw.line: it => {
        set block(spacing: 0pt, above: 0pt, below: 0pt)
        set par(leading: 0.5em)
        pad(bottom: code-line-gap, block(inset: (left: -(numw + numbersep)), grid(
          columns: (numw, 1fr),
          column-gutter: numbersep,
          align: (right + top, left + top),
          text(size: number-size, baseline: 1.8pt)[#it.number],
          it.body,
        )))
      }
      raw(src, lang: "cpp", block: true)
    },
  )
}
#show raw.where(lang: "cpp-ref"): it => code("/" + it.text.trim())

// ---- 说明文件 ----
#show math.equation.where(block: true): set block(above: 6pt, below: 6pt)
#let prose(p) = block(above: 0pt, below: 0pt, {
  set par(leading: 0.48em)
  include p
})
#show raw.where(lang: "typ-prose"): it => prose("/" + it.text.trim())

#let head() = {
  let p = here().page()
  let headings = query(heading).filter(h => h.numbering != none and h.level <= 2)
  let on-page = headings.filter(h => h.location().page() == p)
  let before = headings.filter(h => h.location().page() < p)
  let current = if on-page.len() > 0 { on-page.first() }
    else if before.len() > 0 { before.last() } else { none }
  set text(font: (latin, ..kai), size: 9pt)
  grid(columns: (1fr, auto), align: (left + bottom, right + bottom),
    if current != none {
      numbering(current.numbering, ..counter(heading).at(current.location()))
      h(0.8em)
      current.body
    } else { [Contents] },
    text(size: 16pt)[#counter(page).get().first()],
  )
  v(2pt)
  line(length: 100%, stroke: 0.35pt)
}
#set page(paper: "a4", flipped: true, margin: 13mm, footer: none)

// ---- 单栏封面 → 空白页 → 双栏目录（第 1 页）→ 双栏正文 ----
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
#set page(numbering: "1", header: context head(), footer: context {
  set text(font: latin, size: 9pt)
  align(center)[#counter(page).get().first()]
})
#show outline.entry: set block(above: 2.5pt, below: 2.5pt)
#show outline.entry: set outline.entry(fill: repeat([.], gap: 0.4em))
#show outline.entry.where(level: 1): set block(above: 9pt, below: 3pt)
#show outline.entry.where(level: 1): set text(weight: "bold")
#columns(2)[
  #outline(title: [Contents], depth: 3,
    indent: depth => if depth == 0 { 0pt } else if depth == 1 { 1.5em } else { 3.5em },
  )
]
#pagebreak()

#set page(background: align(center + top, move(dy: 13mm,
  line(angle: 90deg, length: 184mm, stroke: 0.2pt + luma(65%)),
)))
#columns(2)[#include "body.typ"]

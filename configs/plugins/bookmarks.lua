return {
  "tomasky/bookmarks.nvim",
  event = "VimEnter",
  config = function()
    require("bookmarks").setup()
    require("telescope").load_extension("bookmarks")
  end,
}

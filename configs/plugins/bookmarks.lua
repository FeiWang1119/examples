return {
  "tomasky/bookmarks.nvim",
  -- after = "telescope.nvim",
  event = "VimEnter",
  config = function()
    require("bookmarks").setup()
    require("telescope").load_extension("bookmarks")
  end,
}

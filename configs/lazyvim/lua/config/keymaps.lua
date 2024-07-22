-- Keymaps are automatically loaded on the VeryLazy event
-- Default keymaps that are always set: https://github.com/LazyVim/LazyVim/blob/main/lua/lazyvim/config/keymaps.lua
-- Add any additional keymaps here

-- This file is automatically loaded by lazyvim.config.init

-- DO NOT USE THIS IN YOU OWN CONFIG!!
-- use `vim.keymap.set` instead
local map = vim.keymap.set

-- Copy all
map("n", "<C-c>", "<cmd>%y+<cr>", { desc = "Copy all" })

-- Save all
map("n", "<C-a>", "<cmd>wa<cr>", { desc = "Save all" })

-- Exit insert mode
map("i", "jk", "<ESC>", { desc = "exit insert mode" })

-- MarkdownPreview
map("n", "<F12>", "<cmd>MarkdownPreviewToggle<CR>", { desc = "MarkdownPreview" })

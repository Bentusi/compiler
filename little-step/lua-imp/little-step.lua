#! /usr/local/bin/lua

-- ============================================================================
-- Expr
-- ============================================================================
Expr = {}
function Expr:new()
	local self = {}
	setmetatable(self, Expr)
	self.__index = self
	return self
end

-- ============================================================================
-- Num
-- ============================================================================
Num = {}
setmetatable(Num, Expr)
Num.__index = Num
function Num:new(init)
    local self = Expr:new()
    setmetatable(self, Num)
    self.value = init
    return self
end

function Num:to_s()
    return string.format("%s", self.value)
end

function Num:reduceable()
    return false
end

function Num:reduce()
    return self
end

-- ============================================================================
-- Bool
-- ============================================================================
Bool = {}
setmetatable(Bool, Expr)
Bool.__index = Bool
function Bool:new(init)
    local self = Expr:new()
    setmetatable(self, Bool)
    self.value = init
    return self
end

function Bool:to_s()
    return string.format("%s", self.value)
end

function Bool:reduceable()
    return false
end

function Bool:reduce()
    return self
end

-- ============================================================================
-- Add
-- ============================================================================
Add = {}
setmetatable(Add, Expr)
Add.__index = Add
function Add:new(left, right)
    local self = Expr:new()
	setmetatable(self, Add)
    self.l = left
    self.r = right
    return self
end

function Add:to_s()
    return "(" .. self.l:to_s() .. "+" .. self.r:to_s() .. ")"
end

function Add:reduceable()
    return true
end

function Add:reduce()
    if self.l:reduceable() then
        return Add:new(self.l:reduce(), self.r)
    elseif self.r:reduceable() then
        return Add:new(self.l, self.r:reduce())
    else
        return Num:new(self.l.value + self.r.value)
    end
end

-- ============================================================================
-- Mns
-- ============================================================================
Mns = {}
setmetatable(Mns, Expr)
Mns.__index = Mns
function Mns:new(left, right)
    local self = Expr:new()
	setmetatable(self, Mns)
    self.l = left
    self.r = right
    return self
end

function Mns:to_s()
    return "(" .. self.l:to_s() .. "-" .. self.r:to_s() .. ")"
end

function Mns:reduceable()
    return true
end

function Mns:reduce()
    if self.l:reduceable() then
        return Mns:new(self.l:reduce(), self.r)
    elseif self.r:reduceable() then
        return Mns:new(self.l, self.r:reduce())
    else
        return Num:new(self.l.value - self.r.value)
    end
end

-- ============================================================================
-- Mult
-- ============================================================================
Mult = {}
setmetatable(Mult, Expr)
Mult.__index = Mult
function Mult:new(left, right)
    local self = Expr:new()
	setmetatable(self, Mult)
    self.l = left
    self.r = right
    return self
end

function Mult:to_s()
    return "(" .. self.l:to_s() .. "*" .. self.r:to_s() .. ")"
end

function Mult:reduceable()
    return true
end

function Mult:reduce()
    if self.l:reduceable() then
        return Mult:new(self.l:reduce(), self.r)
    elseif self.r:reduceable() then
        return Mult:new(self.l, self.r:reduce())
    else
        return Num:new(self.l.value * self.r.value)
    end
end

-- ============================================================================
-- Div
-- ============================================================================
Div = {}
setmetatable(Div, Expr)
Div.__index = Div
function Div:new(left, right)
    local self = Expr:new()
	setmetatable(self, Div)
    self.l = left
    self.r = right
    return self
end

function Div:to_s()
    return "(" .. self.l:to_s() .. "/" .. self.r:to_s() .. ")"
end

function Div:reduceable()
    return true
end

function Div:reduce()
    if self.l:reduceable() then
        return Div:new(self.l:reduce(), self.r)
    elseif self.r:reduceable() then
        return Div:new(self.l, self.r:reduce())
    else
        return Num:new(self.l.value / self.r.value)
    end
end

-- ============================================================================
-- Lt
-- ============================================================================
Lt = {}
setmetatable(Lt, Expr)
Lt.__index = Lt
function Lt:new(left, right)
    local self = Expr:new()
	setmetatable(self, Lt)
    self.l = left
    self.r = right
    return self
end

function Lt:to_s()
    return "(" .. self.l:to_s() .. "<" .. self.r:to_s() .. ")"
end

function Lt:reduceable()
    return true
end

function Lt:reduce()
    if self.l:reduceable() then
        return Lt:new(self.l:reduce(), self.r)
    elseif self.r:reduceable() then
        return Lt:new(self.l, self.r:reduce())
    else
        return Bool:new(self.l.value < self.r.value)
    end
end

-- ============================================================================
-- Le
-- ============================================================================
Le = {}
setmetatable(Le, Expr)
Le.__index = Le
function Le:new(left, right)
    local self = Expr:new()
	setmetatable(self, Le)
    self.l = left
    self.r = right
    return self
end

function Le:to_s()
    return "(" .. self.l:to_s() .. "<=" .. self.r:to_s() .. ")"
end

function Le:reduceable()
    return true
end

function Le:reduce()
    if self.l:reduceable() then
        return Le:new(self.l:reduce(), self.r)
    elseif self.r:reduceable() then
        return Le:new(self.l, self.r:reduce())
    else
        return Bool:new(self.l.value <= self.r.value)
    end
end

-- ============================================================================
-- Gt
-- ============================================================================
Gt = {}
setmetatable(Gt, Expr)
Gt.__index = Gt
function Gt:new(left, right)
    local self = Expr:new()
	setmetatable(self, Gt)
    self.l = left
    self.r = right
    return self
end

function Gt:to_s()
    return "(" .. self.l:to_s() .. ">" .. self.r:to_s() .. ")"
end

function Gt:reduceable()
    return true
end

function Gt:reduce()
    if self.l:reduceable() then
        return Gt:new(self.l:reduce(), self.r)
    elseif self.r:reduceable() then
        return Gt:new(self.l, self.r:reduce())
    else
        return Bool:new(self.l.value > self.r.value)
    end
end

-- ============================================================================
-- Ge
-- ============================================================================
Ge = {}
setmetatable(Ge, Expr)
Ge.__index = Ge
function Ge:new(left, right)
    local self = Expr:new()
	setmetatable(self, Ge)
    self.l = left
    self.r = right
    return self
end

function Ge:to_s()
    return "(" .. self.l:to_s() .. ">=" .. self.r:to_s() .. ")"
end

function Ge:reduceable()
    return true
end

function Ge:reduce()
    if self.l:reduceable() then
        return Ge:new(self.l:reduce(), self.r)
    elseif self.r:reduceable() then
        return Ge:new(self.l, self.r:reduce())
    else
        return Bool:new(self.l.value > self.r.value)
    end
end

-- ============================================================================
-- Eq
-- ============================================================================
Eq = {}
setmetatable(Eq, Expr)
Eq.__index = Eq
function Eq:new(left, right)
    local self = Expr:new()
	setmetatable(self, Eq)
    self.l = left
    self.r = right
    return self
end

function Eq:to_s()
    return "(" .. self.l:to_s() .. "==" .. self.r:to_s() .. ")"
end

function Eq:reduceable()
    return true
end

function Eq:reduce()
    if self.l:reduceable() then
        return Eq:new(self.l:reduce(), self.r)
    elseif self.r:reduceable() then
        return Eq:new(self.l, self.r:reduce())
    else
        return Bool:new(self.l.value == self.r.value)
    end
end

-- ============================================================================
-- Null
-- ============================================================================
Null = {}
setmetatable(Null, Expr)
Null.__index = Null
function Null:new()
    local self = Expr:new()
	setmetatable(self, Null)
    return self
end

function Null:to_s()
    return "do-nothing"
end

function Null:reduceable()
    return false
end

function Null:reduce()
    return self
end

-- ============================================================================
-- Asgn
-- ============================================================================
Asgn = {}
setmetatable(Asgn, Expr)
Asgn.__index = Asgn
function Asgn:new(name, expr)
    local self = Expr:new()
	setmetatable(self, Asgn)
    self.n = name or ""
    self.expr = expr or Null:new()
    return self
end

function Asgn:to_s()
    return "(" .. self.n .. "=" .. self.v .. ")"
end

function Asgn:reduceable()
    return true
end

function Asgn:reduce(env)
    if self.expr:reduceable() then
        return Asgn:new(self.name, self.expr:reduce())
    else
        env[self.name] = self.v.value
        return Null:new()
    end
end

-- ============================================================================
-- 
-- ============================================================================
function env_to_s(env)
    local str = "{"
    for key, value in pairs(env) do
        str = str .. string.format("(%s=%s)", key, value:to_s())
    end
    return str .. "}"
end

function VM(expr, env)
    print(expr:to_s() .. ", " .. env_to_s(env))
    while expr:reduceable() do
        expr = expr:reduce(env)
        print(expr:to_s() .. ", " .. env_to_s(env))
    end
end

-- ============================================================================
-- 
-- ============================================================================
function main()
    -- local d = Div:new(
    --     Num:new(2.1),
    --     Add:new(Num:new(0), Num:new(0)))
    -- VM(d)

    local env = {}
    env["x"] = Num:new(1)

    local b = Eq:new(
        Num:new(2.0),
        Add:new(Num:new(2), Num:new(3)))
    VM(b, env)
end

main()
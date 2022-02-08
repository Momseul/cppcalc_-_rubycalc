require 'ast'
require 'scanner'
require 'token'
require 'calcex'
require 'bigdecimal'

class Parser
  def initialize(istream)
    @scan = Scanner.new(istream)
  end
  
  def parse()
    return Stmst()
  end
  
  private

  def Stmst()
    t = @scan.getToken
    if t.type != :identifier then
      print "Error 1 ", t.type, ".\n"
      raise ParseError
    end
    a = @scan.getToken
    if a.type != :equal then
      print "Error 2 ", a.type, ".\n"
      raise ParseError.new
    end
    result = Expr()
    a = @scan.getToken
    if a.type != :semicolon then
      print "Error 3 ", a.type, ".\n"
      raise ParseError.new
    end
        a = @scan.getToken
        if a.type == :eol then
          return Stmst()
        end       
    return AssignationNode.new(result, t.lex)
  end
  
  def Expr
    RestExpr(Term())
  end
  
  def RestExpr e

    case @scan.getToken.type
    when :add
      RestExpr(AddNode.new(e,Term()))
    when :sub
      RestExpr(SubNode.new(e,Term()))
    else
      @scan.putBackToken()
      e
    end
  end
  
  def Term
    RestTerm(Storable())
  end
  
  def RestTerm e
    case @scan.getToken.type
    when :times
      RestTerm(TimesNode.new(e,Storable()))
    when :divide
      RestTerm(DivideNode.new(e,Storable()))
    when :module
      RestTerm(ModuleNode.new(e,Storable()))
    else
      @scan.putBackToken()
      e
    end
  end

  def Storable
    MemOperation(Negation())
  end
  
  def MemOperation e #Storable
    #result = Factor()
    t = @scan.getToken
    case t.type
    when :keyword
      if t.lex == "S"
        StoreNode.new e
      elsif t.lex == "P"
        PlusNode.new e
      elsif t.lex == "M"
        MinusNode.new e
      else
        puts "Expected S, P, M; found", t.lex
        raise ParserError.new
      end
    else
      @scan.putBackToken
      e
    end
  end

  def Negation
    t = @scan.getToken
    case t.type
    when :sub
      result = Factor()
      NonNode.new result
    else
      @scan.putBackToken
      result = Factor()
      return result
    end
  end
  
  def Factor
    t = @scan.getToken
    case t.type
    when :number
      NumNode.new t.lex.to_f
    when :identifier
      if t.lex == "call" then
        a = @scan.getToken
        case a.lex
        when "abs"
          ca = @scan.getToken
          if ca.type == :lparen then
            result = Expr()
            ca = @scan.getToken
            if ca.type == :rparen then
              return ABSNode.new result
            else
              puts "Expected )"
              raise ParserError.new
            end
          else
            puts "Expected ( "
            raise ParseError.new
          end
        when "sin"
          ca = @scan.getToken
          if ca.type == :lparen then
            result = Expr()
            ca = @scan.getToken
            if ca.type == :rparen then
              return SINNode.new result
            else
              puts "Expected )"
              raise ParserError.new
            end
          else
            puts "Expected ( "
            raise ParseError.new
          end
        when "cos"
          ca = @scan.getToken
          if ca.type == :lparen then
            result = Expr()
            ca = @scan.getToken
            if ca.type == :rparen then
              return COSNode.new result
            else
              puts "Expected )"
              raise ParserError.new
            end
          else
            puts "Expected ( "
            raise ParseError.new
          end
        when "tan"
          ca = @scan.getToken
          if ca.type == :lparen then
            result = Expr()
            ca = @scan.getToken
            if ca.type == :rparen then
              return TANNode.new result
            else
              puts "Expected )"
              raise ParserError.new
            end
          else
            puts "Expected ( "
            raise ParseError.new
          end
        when "exp"
          ca = @scan.getToken
          if ca.type == :lparen then
            result = Expr()
            ca = @scan.getToken
            if ca.type == :rparen then
              return EXPNode.new result
            else
              puts "Expected )"
              raise ParserError.new
            end
          else
            puts "Expected ( "
            raise ParseError.new
          end
        when "log"
          ca = @scan.getToken
          if ca.type == :lparen then
            result = Expr()
            ca = @scan.getToken
            if ca.type == :rparen then
              return LOGNode.new result
            else
              puts "Expected )"
              raise ParserError.new
            end
          else
            puts "Expected ( "
            raise ParseError.new
          end
        when "sqrt"
          ca = @scan.getToken
          if ca.type == :lparen then
            result = Expr()
            ca = @scan.getToken
            if ca.type == :rparen then
              return SQRTNode.new result
            else
              puts "Expected )"
              raise ParserError.new
            end
          else
            puts "Expected ( "
            raise ParseError.new
          end
        else
          puts "Expected math function"
          raise ParseError.new
        end
      end
        #NO TOCAR
        IDNode.new t.lex
      when :keyword
        if t.lex == "R"
          RecallNode.new
        elsif t.lex == "C"
          ClearNode.new
        else
          puts "Expected R,C; found: ", t.lex
          raise ParserError.new
        end
      when :lparen
        result = Expr()
        t = @scan.getToken
        if t.type == :rparen
          result
        else
          puts "Expected )"
          raise ParserError.new
        end
      else
        puts "Expected number, R, ("
        raise ParserError.new
      end
    end
  end

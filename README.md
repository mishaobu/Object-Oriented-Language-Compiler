# Object-Oriented-Language-Compiler

This is a compiler for an Object Oriented language written in C++.

The following is an example program that the compiler can compile into assembly; please view the [tests page] for more examples.

~~~
class0 {
    integer	member0;

    class0(boolean arg0, integer arg1, boolean arg2) -> none {
        boolean local0;
        integer local1;
        integer i0, i1;
        
        member0 = 107;
        local1 = 244 * 4;
        local0 = 65 >= 57;
        
        i0 = -78;
        while 3 > i0 {
             i0 = i0 * 3;
        
            local0 = false;
            local1 = local1;
            i1 = 34603008;
            while i1 > 33 {
                 i1 = i1 / 4;
            
                local1 = arg1;
                local0 = arg0 and local0;
            }
        }

    }


}

class1 {
    integer	member0;

    f0(boolean arg0, boolean arg1, class0 arg2, integer arg3) -> none {
        boolean local0;
        boolean local1;
        boolean local2;
        boolean local3;
        integer local4;
        
        local4 = 91 + 242;
        local1 = 117 equals 31;
        local0 = false;
        local3 = false;
        local2 = 175 > 133;
        
        if local0 {
            if false {
                local0 = local2;
                local0 = false;
            } else {
                local4 = arg3 - 115 * arg2.member0;
                local0 = arg0;
            }
            
        }
        
        local1 = arg1;

    }

    f1() -> boolean {
        boolean local0;
        integer local1;
        integer i0;
        
        local1 = -185;
        local0 = true or true;
        
        local1 = 58;
        i0 = 400;
        while i0 >= 50 {
             i0 = i0 / 2;
        
            print local0;
            f0(false, local0, new class0(local0, member0, 227 equals local1), 65 / 62);
            local0 = local0;
        }
        print local0;
        print true;
        return local0;

    }

    f2(boolean arg0, class0 arg1, integer arg2, class0 arg3) -> boolean {
        class0 local0;
        boolean local1;
        
        local1 = false;
        local0 = new class0(not (false or true), -109, false and false);
        
        if arg2 equals local0.member0 and false {
            if true {
                f0(arg0, true, arg3, arg2);
            }
            
            f0(local0.member0 equals member0 + 135, not (false), new class0(true or false, 34, arg0), 216);
        }
        
        f0((true), false, arg3, 229 / arg2);
        return arg0;

    }

    f3(integer arg0) -> none {
        
        
        f0(f1(), true, new class0((arg0 > 44), arg0, true), arg0);

    }

    f4(integer arg0) -> integer {
        boolean local0;
        integer i0;
        
        local0 = true;
        
        i0 = -50;
        while -2 >= i0 {
             i0 = i0 + 4;
        
            print (local0);
            f0(local0, false, new class0(arg0 > member0, 180, member0 equals 71 / member0), 114);
        }
        return member0 - 128;

    }

    class1(integer arg0, integer arg1, integer arg2, integer arg3) -> none {
        integer local0;
        integer local1;
        integer i0, i1, i2, i3;
        
        member0 = 231 / 103;
        local1 = 156;
        local0 = 18;
        
        i0 = -8;
        while i0 >= -28 {
             i0 = i0 - 10;
        
            print arg1;
            i1 = 52;
            while 295 > i1 {
                 i1 = i1 * 3;
            
                local0 = 154 / 84;
            }
            f0(true, false, new class0(f2(48 > 254, new class0(40 > 82, 81, false), arg2, new class0(68 > local1, (member0), false)), member0 / member0, not (true)), arg0);
        }
        local1 = arg1;
        i2 = -69;
        while i2 > -93 {
             i2 = i2 + -6;
        
            i3 = -44;
            while 58 > i3 {
                 i3 = i3 - -6;
            
                print 222;
                f0(false or true, true, new class0(not (true), 241, arg0 equals arg2), 112);
                f0(true, not (false), new class0(false, 226, local0 equals member0), member0);
            }
            if 137 equals local1 and false {
                local1 = 236;
            } else {
                local0 = 252 - arg2;
                print arg2;
            }
            
        }

    }


}

class2 {
    class1	member0;
    integer	member1;
    integer	member2;
    integer	member3;
    boolean	member4;

    f0(integer arg0, boolean arg1, integer arg2, boolean arg3) -> boolean {
        integer local0;
        integer local1;
        integer i0, i1, i2, i3, i4;
        
        local1 = 9;
        local0 = 22;
        
        i0 = -72;
        while 18 >= i0 {
             i0 = i0 - -6;
        
            member0.f3(member3 + member2 * -118);
            member0.f0(false, member1 equals local1, new class0(member2 * 37 equals member3, 35, false), 75);
            local1 = member0.f4(144);
        }
        if not (true) {
            local1 = member1 / 73;
            local0 = 66;
            i1 = -69;
            while i1 >= -89 {
                 i1 = i1 + -2;
            
                print not (arg1);
                local1 = member0.member0;
                local1 = member0.member0;
            }
        } else {
            if member2 equals 79 {
                i2 = 85;
                while 121 >= i2 {
                     i2 = i2 + 2;
                
                    i3 = -86;
                    while i3 >= -230 {
                         i3 = i3 - 8;
                    
                        i4 = 73;
                        while i4 >= -22 {
                             i4 = i4 + -5;
                        
                            local0 = member2 / member3;
                            member0.f0(false and true, arg3, new class0(member0.f1(), member3, arg3), member1);
                        }
                    }
                    member0.f0(member0.member0 >= 99, arg3, new class0(false, arg0, arg3), 100);
                }
                print arg2;
                print 158 - member2;
            } else {
                local0 = arg0;
            }
            
            local0 = arg0 + 3;
            print local1;
        }
        
        return arg1;

    }

    f1(boolean arg0, integer arg1, boolean arg2, integer arg3, class1 arg4) -> boolean {
        integer local0;
        integer i0;
        
        local0 = 103 + 193;
        
        if true {
            arg4.f3(arg3 * member2);
            local0 = 131;
        }
        
        arg4.f0(arg3 equals (member1), member4, new class0(arg4.f2(((member4)), new class0(20 > member2, arg1, true), 64, new class0((false), 158, member4)), 134, arg0), -178);
        local0 = member2;
        i0 = 61;
        while 1085 >= i0 {
             i0 = i0 * 4;
        
            local0 = arg4.member0;
            arg4.f3(120 - 119);
        }
        return true;

    }

    f2(integer arg0, boolean arg1) -> integer {
        boolean local0;
        boolean local1;
        integer i0;
        
        local1 = false;
        local0 = 13 >= 78;
        
        member0.f3(member0.member0 * member0.member0);
        if local1 {
            i0 = -30;
            while 994 >= i0 {
                 i0 = i0 * 2;
            
                member0.f0(175 + 0 > member0.member0, local0, new class0(false, member0.f4(135), false and true), 82);
            }
            local1 = true;
        }
        
        local0 = member2 > 237;
        print -member3;
        return member1;

    }

    f3(integer arg0) -> boolean {
        
        
        print false;
        print arg0;
        print 69;
        return true;

    }

    f4(integer arg0) -> class0 {
        integer local0;
        class0 local1;
        class1 local2;
        boolean local3;
        integer local4;
        integer i0, i1, i2;
        
        local4 = 176;
        local1 = new class0(true, 130 * 167, 54 - 116 >=127 );
        local0 = 195;
        local3 = 18 equals 139;
        local2 = new class1(80, 164 * 106 * 93, 182, 121);
        
        i0 = -52;
        while i0 > -54 {
             i0 = i0 + -2;
        
            print member4;
        }
        if arg0 equals local0 {
            i1 = 20971520;
            while i1 >= 80 {
                 i1 = i1 / 4;
            
                print 59 > 128;
            }
            local2.member0 = 251 + -148;
            if member4 {
                local3 = member4;
                i2 = -48;
                while i2 > -132 {
                     i2 = i2 + -6;
                
                    print 247 >= 105;
                }
            } else {
                local0 = 105;
                print member4 and true;
                if member4 and member4 {
                    local4 = f2(142, true or local3 or false) - 169;
                    local1.member0 = 184;
                }
                
            }
            
        } else {
            local2.member0 = 103;
        }
        
        print 224 / 67;
        return local1;

    }

    class2() -> none {
        integer local0;
        integer local1;
        boolean local2;
        integer local3;
        integer local4;
        
        member4 = 61 > 98;
        member1 = 57 - 54;
        member0 = new class1(204, -172, 115, 69 - (123));
        member3 = 138;
        member2 = 55 - 239;
        local4 = 253 / 171;
        local1 = 119;
        local0 = 26;
        local3 = 19;
        local2 = true;
        
        member0.f0((member4), member4, new class0(11 equals local3, local3, local2 or local2), -108);
        print 246 / member3;

    }


}

Main {


    main() -> none {
        boolean local0;
        integer local1;
        class0 local2;
        integer local3;
        integer i0, i1;
        
        local1 = 201;
        local0 = 29 equals 26;
        local3 = 173 + 67;
        local2 = new class0(false, 59, (true));
        
        i0 = 160;
        while i0 >= 10 {
             i0 = i0 / 4;
        
            print -59;
            print local1;
            if local0 {
                local2.member0 = 84;
            } else {
                print (47);
                local0 = local0;
                i1 = 3;
                while 1027 > i1 {
                     i1 = i1 * 2;
                
                    local2.member0 = 33;
                }
            }
            
        }
        if local0 {
            local2.member0 = (68);
            if local1 + 255 > local1 {
                local0 = local0;
            }
            
        }
        
        local3 = local1;
        if local0 {
            local3 = 54;
        }
        
        print local0;
        print false;

    }


}~~~

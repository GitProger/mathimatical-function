#ifndef __FUN_HPP_INC
#define __FUN_HPP_INC
class NotConstantFunctionException : private std::exception
    {};

class MathFunction {
    private:
        int degree; //proplems with '-' degreeses
                    //@example:
                    // x^2 / x^3
                     //@or:
                    // x^3 / (x^2 + 1)
                    // degree = 1, but answer is not 'x'
        std::vector<long double> koef;
        
        void operator <<= (int cnt) {
            std::vector<long double> buffer = this->koef;
            this->degree += cnt;
            this->koef = std::vector<long double>(buffer.size() + cnt);
            for (int i = cnt; i < this->koef.size(); i++)
                this->koef[i] = buffer[i - cnt];
        }
        
        void operator >>= (int cnt) {
            std::vector<long double> buffer = this->koef;
            this->degree -= cnt;
            this->koef = std::vector<long double>(buffer.size() - cnt);
            for (int i = 0; i < this->koef.size(); i++)
                this->koef[i] = buffer[i + cnt];
        }
        
    public:
        MathFunction(long double cnst = 0.0) {
            this->degree = 0;
            this->koef = vector<long double>({cnst});
        }

        MathFunction(const std::vector<long double> &il) {
            this->koef = il;
            this->degree = il.size() - 1;
            if (il.size())
                for (int i = 0; i <= this->degree; i++)
                    this->koef[i] = il[this->degree - i];
        } 
    
        MathFunction(int deg, const std::vector<long double> &il) {
            this->koef = vector<long double>(deg + 1);
            this->degree = deg;
            if (il.size())
                for (int i = 0; i <= this->degree; i++)
                    this->koef[i] = il[this->degree - i];
        } 
        ~MathFunction() {}
        
        operator long double() const {
             if (this->degree == 0)
                 return this->koef[0];
             else
                 throw NotConstantFunctionException();
        }
    
        long double operator () (long double Xarg) const {
            long double r = 0.0;
            for (int i = 0; i <= this->degree; i++)
                r += this->koef[i] * pow(Xarg, i);
            return r;
        }
        
        int Deg() const { return this->degree; }
        std::vector<long double> GetKoef() { return this->koef; }
        
        
        MathFunction operator - () const {
            MathFunction F = *this;
            for (int i = 0; i <= this->degree; i++)
                F.koef[i] *= -1.0;
            return F;
        }
        
        MathFunction operator + (const MathFunction &G) const {
            MathFunction F = *this;
            if (F.degree >= G.degree) {
                for (int i = 0; i <= G.degree; i++)
                    F.koef[i] += G.koef[i];
            } else {
                MathFunction Buf = G;
                for (int i = 0; i <= F.degree; i++)
                    Buf.koef[i] += F.koef[i];
                F = Buf;
            }
            return F;
        }

        MathFunction operator * (long double constant) const {
            MathFunction F = *this;
            for (int i = 0; i <= F.degree; i++)
                F.koef[i] *= constant;
            return F;
        }

        MathFunction operator * (const MathFunction &G) const {
            MathFunction F(this->degree + G.degree, {});
            std::vector<MathFunction> v;
            for (int i = 0; i <= this->degree; i++) {
                MathFunction Buf = G * this->koef[i];
                Buf <<= i;
                v.push_back(Buf);
            }
            for (auto val : v)
                F = F + val;
            return F;
        }
        
        
        MathFunction operator / (const MathFunction &G) const {
            MathFunction F(this->degree - G.degree, {});
            /* division... */
            return F;
        }
        friend std::ostream &operator << (std::ostream &out, const MathFunction &f);
};
        
std::ostream &operator << (std::ostream &out, const MathFunction &f) {
    std::vector<long double> koef = f.GetKoef();
    int deg = f.Deg();
    if (deg == 0) {
        out << koef[0];
        return out;
    }
    if (f.Deg() == 1) {
        out 
            << koef[1]
            << "x";        
        goto last;
    }

    if (koef[deg] > 0.0) {
        if (koef[deg] != 1.0) out << koef[deg];
        out << "x^" << deg;
    } else if (koef[deg] < 0.0) {
        out << "-";
        if (koef[deg] != -1.0) out << -koef[deg];
        out << "x^" << deg;
    }
    for (int i = deg - 1; i > 1; i--) {
        if (koef[i] == 0.0) continue;
        if (koef[i] > 0.0) {
            out << " + ";
            if (koef[i] != 1.0) out << koef[i];
            out << "x^" << i;
        } else {
            out << " - ";
            if (koef[i] != -1.0) out << -koef[i];
            out << "x^" << i;
        }
    }
    if (koef[1])
        if (koef[1] > 0.0) {
            out << " + ";
            if (koef[1] != 1.0) out << koef[1];
            out << "x";
        } else if (koef[1] < 0.0) {
            out << " - ";
            if (koef[1] != -1.0) out << -koef[1];
            out << "x";
        }
  last:
    if (koef[0] > 0.0)
        out << " + " << koef[0];
    else if (koef[0] < 0.0)
        out << " - " << -koef[0];
    return out;
} 

#endif

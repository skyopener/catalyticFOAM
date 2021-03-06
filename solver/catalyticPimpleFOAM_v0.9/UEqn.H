    fvVectorMatrix UEqn
    (
        fvm::ddt(rho, U)
      + fvm::div(phi, U)
      - fvm::laplacian(mu, U)
      - fvc::div(mu*dev2(fvc::grad(U)().T()))
     ==
        rho*g
      + fvOptions(rho, U)
    );

    UEqn.relax();

    fvOptions.constrain(UEqn);

    if (pimple.momentumPredictor())
    {
        solve(UEqn == -fvc::grad(p));

        fvOptions.correct(U);
    }

     Info << " Umin: " << min(U).value() << " Umax: " << max(U).value() << endl;
